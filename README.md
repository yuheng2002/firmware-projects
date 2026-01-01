# Embedded Firmware Learning Journey

This repository documents my self-study projects in **Bare-Metal Embedded C** programming using the **STM32 (ARM Cortex-M)** platform.

My goal for Winter 2025 is to bridge the gap between my software coursework (**CSE 29: Systems Programming**) and hardware fundamentals (**ECE 35: Analog Design**) by building low-level drivers from scratch. I focus on direct register manipulation rather than relying on high-level abstraction libraries like Arduino.

## 🚧 Planned Projects (Winter Break 2025)

### Project 1: Interrupt-Driven LED State Machine
**Concept:** A responsive I/O subsystem designed to handle user input efficiently without blocking CPU execution.

**Technical Focus:**
* **Event-Driven Architecture:** Replace inefficient "polling" loops with **Hardware Interrupts (ISR)** to capture button presses immediately.
* **Finite State Machine (FSM):** Structure the C code using `switch/case` logic to manage transitions between LED modes (Solid, Blink, Breathe).
* **Signal Integrity:** Implement software **debouncing** algorithms to handle the physical noise of mechanical switches.

### Project 2: PWM Actuator Driver & Hardware Timers
**Concept:** A bare-metal driver utilizing STM32 General Purpose Timers to generate precision Pulse Width Modulation (PWM) signals. This project focuses on non-blocking actuator control logic (e.g., dynamic LED brightness breathing effects) without relying on CPU delay loops.

**Technical Focus:**
* **Hardware Timers (TIMx):** Direct configuration of Prescalers (`PSC`) and Auto-Reload Registers (`ARR`) to establish precise time bases and frequencies independent of the CPU clock.
* **PWM Generation:** Manipulation of Capture/Compare Registers (`CCR`) to dynamically adjust duty cycles, enabling analog-like control over digital pins.
* **Alternate Function Mapping:** Configuring GPIO modes to route internal timer peripherals to physical output pins using Alternate Function Registers (`AFR`).
* 
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
