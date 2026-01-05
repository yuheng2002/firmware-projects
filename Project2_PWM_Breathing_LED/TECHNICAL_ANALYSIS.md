# Technical Analysis: Hardware PWM & Timer Logic

## 1. The Mathematics of Frequency (PSC & ARR)

[cite_start]The STM32F446RE is powered by a **16 MHz System Clock (HSI)**[cite: 468]. [cite_start]While this speed is powerful, it is too fast for directly driving visible LED effects[cite: 469]. [cite_start]To control the frequency, we use two key registers: the **Prescaler (PSC)** and the **Auto-Reload Register (ARR)**[cite: 470].

### The Calculation Logic
[cite_start]The Timer frequency is determined by the following formula[cite: 472, 473]:

```math
Timer_Freq = System_Clk / ((PSC + 1) * (ARR + 1))

```

* 
**PSC (The Gearbox):** This scales down the clock.


* At `PSC = 0`: The timer counts at 16 MHz (62.5 ns per tick).


* At `PSC = 15`: The timer counts at `16 MHz / 16 = 1 MHz` (1 µs per tick).




* 
**ARR (The Cycle Length):** This defines how many ticks constitute one full cycle (period).


* With `ARR = 999`, the timer counts 1000 steps (0 to 999).





**Current Configuration:**

```text
Target: 1 kHz Frequency
Calculation:
16,000,000 / ((15 + 1) * (999 + 1)) 
= 16,000,000 / (16 * 1000) 
= 1,000 Hz (1 kHz)

```

At **1 kHz**, the LED blinks 1000 times per second. Due to the **Persistence of Vision**, the human eye integrates this high-speed flickering into a steady light.

### The "Frame Rate" Analogy (Why Pre-scaling Matters)

I experimented with `PSC = 1600` (keeping ARR=999).

* 
**Result:** Frequency drops to **10 Hz**.


* 
**Observation:** The LED flickering became visually painful and "laggy".


* 
**Analogy:** This is identical to playing a video game at **10 FPS**. The hardware updates are too slow for the human eye to perceive as continuous motion. Just as a 144Hz monitor looks smoother than a 60Hz one, a 1 kHz LED PWM looks smoother than 10 Hz.



---

## 2. Design Trade-offs: Resolution vs. Range

If `PSC` and `ARR` are inversely proportional, why not just use `PSC=0` and a massive `ARR`? There are three engineering reasons for balancing them:

1. **Counter Overflow (32-bit Limit):** TIM2 is a 32-bit timer, counting up to approx. 4.29 billion. Running at full 16 MHz without prescaling would cause the counter to overflow too quickly for long-duration tasks. Prescaling allows us to measure longer time durations with the same number of bits.


2. 
**Power Consumption:** Higher clock frequencies increase dynamic power consumption. Running the counter at 16 MHz consumes more energy than at 1 MHz. For battery-powered devices, lowering the peripheral clock is a critical optimization.


3. **Resolution (Granularity):** * **High Resolution:** Low PSC, High ARR. This provides more "brightness steps" (e.g., 1000 steps) for smooth fading.


* **Low Resolution:** High PSC, Low ARR. If ARR is only 10, the "breathing" effect would look like a jagged staircase (10%, 20%, etc.).


* 
**Optimization:** The current config (1 MHz tick, 1000 steps) offers a perfect balance of smoothness and efficiency.





---

## 3. Register Configuration Logic

### A. CR1 (Control Register 1)

* 
**Role:** The Ignition Key.


* 
**Logic:** Without setting the `CEN` (Counter Enable) bit, the internal clock tree is gated off and the counter stays at 0.



### B. CCMR1 (Capture/Compare Mode Register 1)

* 
**Role:** The Logic Controller.


* 
**Setting:** Bits 6:4 set to `110` (PWM Mode 1).


* 
**Mechanism:** This sets the rule for the **Hardware Comparator**:


* **Upcounting Logic:**
* If `CNT < CCR1`: Output is **Active**.


* If `CNT >= CCR1`: Output is **Inactive**.






* 
**Clarification:** By default, **Active = Logic High (3.3V)** and **Inactive = Logic Low (0V)**. When CNT is below the threshold, the LED is ON. This is handled purely by hardware gates.



### C. CCER (Capture/Compare Enable Register)

* 
**Role:** The Output Gate.


* 
**Logic:** The signal cannot leave the peripheral to reach pin PA5 unless `CC1E` (Bit 0) is set. It acts as the physical switch connecting Timer logic to the GPIO.



### D. CCR1 (Capture/Compare Register 1)

* 
**Role:** The Threshold (Duty Cycle).


* 
**Logic:** This 32-bit value is the reference point for the Comparator. Changing this value changes when the signal flips from High to Low in the cycle.



---

## 4. Software-Hardware Interaction (The "Breathing" Logic)

This project demonstrates the **Separation of Time Domains**:

* 
**Hardware Domain (Fast):** The Timer (TIM2) runs at **1 kHz**, completing a full PWM cycle every **1 ms** .


* **Software Domain (Slow):** The CPU runs the `main()` loop. `software_delay()` pauses the CPU for approx. **5-10 ms** .



**Interaction:**

1. Software sets brightness to `200/999`.


2. Software sleeps for 5 ms.


3. 
**During this sleep, Hardware runs 5 full PWM cycles** at exactly 20% duty cycle.


4. Software wakes up and sets brightness to `201/999`.



**Why do we need the delay?**
The delay controls the **Animation Speed**, not the LED frequency. Without `software_delay`, the 16MHz CPU would update the brightness so fast that the human eye would only see a blur of average brightness. The delay slows down the rate of change so we can perceive the "Breathing" effect.

```

Would you like me to help you draft the next project description for your smart cat feeder or help you set up the I2C driver for its sensors?

```
