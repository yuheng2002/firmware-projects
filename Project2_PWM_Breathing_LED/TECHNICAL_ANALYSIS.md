# Technical Analysis: Hardware PWM & Timer Logic

## 1. The Mathematics of Frequency (PSC & ARR)

The STM32F446RE is powered by a **16 MHz System Clock (HSI)**. While this speed is powerful, it is too fast for directly driving visible LED effects. To control the frequency, we use two key registers: the **Prescaler (PSC)** and the **Auto-Reload Register (ARR)**.

### The Calculation Logic
The Timer frequency is determined by the following formula:

$$Timer\_Freq = \frac{System\_Clk}{(PSC + 1) \times (ARR + 1)}$$

---

* **PSC (The Gearbox):** This scales down the clock.
* At `PSC = 0`: The timer counts at 16 MHz (62.5 ns per tick).
* At `PSC = 15`: The timer counts at `16 MHz / 16 = 1 MHz` (1 µs per tick).


* **ARR (The Cycle Length):** This defines how many ticks constitute one full cycle (period).
* With `ARR = 999`, the timer counts 1000 steps (0 to 999).



**Current Configuration:**

```text
Target: 1 kHz Frequency
Calculation:
16,000,000 / ((15 + 1) * (999 + 1)) 
= 16,000,000 / (16 * 1000) 
= 1,000 Hz (1 kHz)

```

At **1 kHz**, the LED blinks 1000 times per second. Due to the **Persistence of Vision**, the human eye integrates this into a steady light.

### The "Frame Rate" Analogy (Why Pre-scaling Matters)

I experimented with `PSC = 1600` (keeping ARR=999).

* **Result:** Frequency drops to **10 Hz**.
* **Observation:** The LED flickering became visually painful and "laggy."
* **Analogy:** This is identical to playing a video game at **10 FPS**. The hardware updates are too slow for the human eye to perceive as continuous motion. Just as a 144Hz monitor looks smoother than a 60Hz one, a 1 kHz LED PWM looks smoother than 10 Hz.

## 2. Design Trade-offs: Resolution vs. Range

If `PSC` and `ARR` are inversely proportional, why not just use `PSC=0` and a massive `ARR`? Or a massive `PSC` and tiny `ARR`? There are three engineering reasons for balancing them:

1. **Counter Overflow (32-bit Limit):**
TIM2 is a 32-bit timer, meaning the maximum count value is roughly 4.29 billion (`2^32 - 1`). If we run at full 16 MHz without prescaling, a simple delay calculation could quickly overflow the counter. Prescaling allows us to measure longer time durations with the same number of bits.
2. **Power Consumption:**
High-frequency switching consumes more power (CMOS dynamic power consumption is proportional to frequency: `P ∝ f`). Running the timer counter at 16 MHz consumes more energy than running it at 1 MHz. For battery-powered devices, lowering the peripheral clock is a critical optimization.
3. **Resolution (Granularity):**
* **High Resolution:** Low PSC, High ARR. This gives us thousands of "brightness steps" for smooth fading.
* **Low Resolution:** High PSC, Low ARR. If ARR is only 10, we only have 10 brightness levels (10%, 20%... 100%). The "breathing" effect would look like a jagged staircase rather than a smooth curve.
* **Optimization:** The current config (1 MHz tick, 1000 steps) offers a perfect balance of smoothness and efficiency.



## 3. Register Configuration Logic

To enable this behavior, specific registers must be configured beyond just PSC/ARR.

### A. CR1 (Control Register 1)

* **Role:** The Ignition Key.
* **Logic:** The Timer is a digital circuit. Without setting the `CEN` (Counter Enable) bit, the internal clock tree is gated off, and the counter stays at 0.

### B. CCMR1 (Capture/Compare Mode Register 1)

* **Role:** The Logic Controller.
* **Setting:** Bits 6:4 set to `110` (PWM Mode 1).
* **Mechanism:** This sets the rule for the **Hardware Comparator**:
* **Upcounting Logic:**
* If `CNT < CCR1`: Output is **Active**.
* If `CNT >= CCR1`: Output is **Inactive**.




* **Clarification on "Active/Inactive":**
* By default, **Active = Logic High (3.3V)** and **Inactive = Logic Low (0V)**.
* Therefore, when CNT is below the threshold, the LED is ON. This logic is handled purely by hardware gates, independent of the CPU.



### C. CCER (Capture/Compare Enable Register)

* **Role:** The Output Gate.
* **Logic:** Even if the Timer calculates the waveform internally, the signal cannot leave the peripheral block to reach pin PA5 unless `CC1E` (Bit 0) is set. It acts as the physical switch connecting the Timer's logic to the GPIO Pin.

### D. CCR1 (Capture/Compare Register 1)

* **Role:** The Threshold (Duty Cycle).
* **Logic:** This 32-bit value is the reference point for the Comparator. By changing this value, we change *when* the signal flips from High to Low in the cycle.

## 4. Software-Hardware Interaction (The "Breathing" Logic)

This is the most critical concept: **The separation of Time Domains.**

### The Hardware Domain (Fast)

* The Timer (TIM2) is running at **1 kHz**.
* It completes a full PWM cycle (0% to 100% logic check) every **1 ms**.

### The Software Domain (Slow)

* The CPU runs the `main()` loop.
* Inside the loop, `software_delay()` pauses the CPU for (approx) **5-10 ms**.
* **Interaction:**
1. Software sets brightness to `200/999`.
2. Software sleeps for 5 ms.
3. **During this sleep, Hardware runs 5 full PWM cycles** at exactly `200/999` duty cycle.
4. Software wakes up, sets brightness to `201/999`.
5. Repeat.


### Why do we need the delay?

The delay does not control the *LED frequency*; it controls the *Animation Speed*.
Without `software_delay`, the 16MHz CPU would blast through values 0 to 999 in microseconds. The LED would fade in and out so fast that the human eye would just see a blur of average brightness. The delay slows down the **rate of change**, allowing us to perceive the "Breathing" effect.
