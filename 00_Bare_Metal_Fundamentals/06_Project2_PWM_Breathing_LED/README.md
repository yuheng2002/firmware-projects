# Project 2: PWM Breathing LED (Bare-Metal STM32)

## 📖 Overview
This project implements a **Breathing LED effect** on the STM32F446RE Nucleo board using **Hardware PWM (Pulse Width Modulation)**.

Unlike typical beginner projects that use blocking delays to toggle pins (Software PWM), this project utilizes the STM32's internal **General Purpose Timer (TIM2)** to generate the waveform. The CPU's only responsibility is to modulate the duty cycle over time, leaving the high-frequency signal generation entirely to the hardware peripheral.

**Key Technical Focus:**
- **Bare-Metal Programming:** No HAL, no LL, no Standard Peripheral Library. Pure C interacting with Memory-Mapped Registers.
- **Hardware Abstraction:** Custom-written drivers for GPIO and Timer peripherals.
- **Alternate Functions:** Configuring GPIO pins to hand over control to internal timers.
- **PWM Generation:** Understanding Prescalers (PSC), Auto-Reload (ARR), and Capture/Compare (CCR).

---

## 🛠 Hardware & Tools
* **Board:** ST Nucleo-F446RE (ARM Cortex-M4)
* **MCU:** STM32F446RE
* **Actuator:** On-board User LED (LD2) connected to **PA5**
* **IDE:** STM32CubeIDE (for compilation and flashing)
* **Debugger:** ST-Link V2-1 (On-board)

---

## ⚙️ Architecture & Logic

### 1. The "Signal Chain"
How the 16MHz CPU clock is transformed into a visible breathing effect:

1.  **Clock Source:** HSI (Internal Oscillator) @ 16 MHz.
2.  **Prescaler (PSC):** Divides clock by 16 → **1 MHz** (1 tick = 1 µs).
3.  **Auto-Reload (ARR):** Sets the counter limit to 999.
    * Frequency = 1 MHz / 1000 ticks = **1 kHz** (Stable, flicker-free light).
4.  **Capture/Compare (CCR1):** Controls the **Duty Cycle** (Brightness).
    * If `CNT < CCR1`: Output High (LED ON).
    * If `CNT >= CCR1`: Output Low (LED OFF).
5.  **GPIO Output:** The signal is routed to Pin **PA5** via Alternate Function **AF1**.

### 2. Hardware vs. Software Roles
One of the most important concepts demonstrated in this project is the separation of concerns:

| Component | Responsibility | Behavior if System Crashes |
| :--- | :--- | :--- |
| **Hardware (TIM2)** | **Signal Generation.** Continuously toggles the pin at 1kHz based on the current `CCR1` value. | **Continues working.** The LED will stay lit at the last set brightness level. |
| **Software (CPU)** | **Modulation.** Updates the `CCR1` register every few milliseconds to create the "fade-in/fade-out" animation. | **Stops.** The breathing animation halts, but the light does not turn off. |

---

## 🔌 Pin Mapping

| GPIO Port | Pin Number | Mode | Alternate Function | Connected Peripheral | Description |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **GPIOA** | **5** | Alternate Function | **AF1** | **TIM2_CH1** | PWM Output to LED |

---

## 📂 File Structure

```text
06_Project2_PWM_Breathing_LED/
├── Sources/
│   ├── main.c                          # Main Application Logic (Brightness Loop)
│   ├── stm32f446xx.h                   # Main MCU Header (Base Addresses, Register Structs)
│   ├── stm32f446xx_gpio_driver.h       # GPIO Driver Header (Pin Configuration)
│   ├── stm32f446xx_gpio_driver.c       # GPIO Driver Implementation
│   ├── stm32f446xx_timer_driver.h      # Timer Driver Header (PWM Configuration)
│   └── stm32f446xx_timer_driver.c      # Timer Driver Implementation
└── Startup/
    └── ...                             # Startup code (Reset Handler)
```
---

## 🚀 How to Build & Run
Open STM32CubeIDE.

Import this folder as an existing project.

Build the project (Hammer icon).

Connect Nucleo-F446RE via USB.

Run/Debug.

Observe: The Green LED (PA5) should smoothly fade in and out.
---

## 🧠 Learning Notes
Lookup Logic: To find which Alternate Function controls the LED, I used the Datasheet (Table 11), not the Reference Manual.

Mapping: PA5 + AF1 -> TIM2_CH1.

Bit Manipulation: Using generic macros (SET_BIT, CLEAR_BIT) makes code readable and prevents overwriting adjacent bits.

Safety First: In TIM_PWM_Init, we clear the register bits (e.g., CCMR1) before setting them to ensure no residual configuration causes bugs.
