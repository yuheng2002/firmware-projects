# Embedded Firmware Learning Journey

This repository documents my self-study projects in **Bare-Metal Embedded C** programming using the **STM32 (ARM Cortex-M)** platform.

My goal for Winter 2025 is to bridge the gap between my software coursework (**CSE 29: Systems Programming**) and hardware fundamentals (**ECE 35: Analog Design**) by building low-level drivers from scratch. I focus on direct register manipulation rather than relying on high-level abstraction libraries like Arduino.

## 🚧 Planned Projects (Winter Break 2025)

### Project 1: Temperature-Controlled Cooling System
**Concept:** A closed-loop control system that dynamically adjusts fan speed based on ambient temperature.

**Technical Focus:**
* **Communication Protocol:** Implement **I2C** driver logic to interface with a digital temperature sensor (e.g., TC74 or BMP280).
* **Actuator Control:** Configure **Hardware Timers** to generate **PWM (Pulse Width Modulation)** signals for motor speed control.
* **Hardware Interface:** Use a MOSFET driver circuit (treating it as a voltage-controlled switch) to bridge the 3.3V MCU logic with a 12V DC fan.

### Project 2: Interrupt-Driven LED State Machine
**Concept:** A responsive I/O subsystem designed to handle user input efficiently without blocking CPU execution.

**Technical Focus:**
* **Event-Driven Architecture:** Replace inefficient "polling" loops with **Hardware Interrupts (ISR)** to capture button presses immediately.
* **Finite State Machine (FSM):** Structure the C code using `switch/case` logic to manage transitions between LED modes (Solid, Blink, Breathe).
* **Signal Integrity:** Implement software **debouncing** algorithms to handle the physical noise of mechanical switches.

---

## 🛠 Hardware & Tools

* **Microcontroller:** STM32 Nucleo-64 (ARM Cortex-M4)
* **Language:** C (Standard C99/C11)
* **Peripherals:** GPIO, Timers (TIM), NVIC (Interrupt Controller), I2C
* **Development Environment:** STM32CubeIDE / GCC / Makefiles
* **Electronics:** Breadboard, LEDs, Push-buttons, Logic Level MOSFET, External Power Supply

## 📚 Background
* **Software:** C Pointers, Memory Management, Bitwise Operations (from CSE 29).
* **Hardware:** KCL/KVL, Circuit Analysis (from ECE 35).
