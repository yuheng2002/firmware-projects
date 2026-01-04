# Embedded Firmware Learning Journey

This repository documents my projects in **Bare-Metal Embedded C** programming using the **STM32 (ARM Cortex-M)** platform.

**Objective:** To bridge the gap between my software systems coursework (**CSE 29**) and hardware fundamentals (**ECE 35**) by building low-level drivers from scratch. The focus is on **direct register manipulation**, deliberately avoiding high-level abstraction libraries like Arduino or HAL to understand the underlying architecture.

## 📂 Project Portfolio

### Project 1: Interrupt-Driven LED State Machine
* **Status:** ✅ Completed
* **Concept:** A responsive I/O subsystem designed to handle user input efficiently without blocking CPU execution.

**Technical Focus:**
* **Event-Driven Architecture:** Replaced inefficient "polling" loops with **Hardware Interrupts (ISR)** to capture button presses immediately.
* **Finite State Machine (FSM):** Structured the C code to manage transitions between LED modes (Solid, Blink, Off) based on user input.
* **Signal Handling:** Implemented software logic to handle the mechanical behavior of the on-board user button.

### Project 2: PWM Actuator Driver & Hardware Timers
* **Status:** ✅ Completed
* **Concept:** A bare-metal driver utilizing STM32 General Purpose Timers to generate precision Pulse Width Modulation (PWM) signals. This project implements a "Breathing LED" effect by offloading high-frequency signal generation to hardware.

**Technical Focus:**
* **Hardware Timers (TIMx):** Direct configuration of Prescalers (`PSC`) and Auto-Reload Registers (`ARR`) to establish a precise 1kHz time base independent of the CPU clock.
* **PWM Generation:** Manipulation of Capture/Compare Registers (`CCR`) to dynamically adjust duty cycles, enabling analog-like control over digital pins.
* **Alternate Function Mapping:** Configured GPIO Mode and Alternate Function Registers (`AFR`) to route the internal TIM2 peripheral to the physical PA5 pin (bypassing standard GPIO output).

---

## 🛠 Hardware & Tools

* **Microcontroller:** STM32 Nucleo-64 (ARM Cortex-M4 / STM32F446RE)
* **Language:** C (Standard C99/C11)
* **Peripherals Used:** GPIO, General Purpose Timers (TIM2), NVIC (Interrupt Controller), RCC (Clock Control)
* **Development Environment:** STM32CubeIDE / GCC / Makefiles
* **Hardware Setup:** Utilized **On-board User LED (LD2)** and **User Button (B1)** for rapid prototyping and driver verification.

## 📚 Background
* **Software:** C Pointers, Memory Management, Bitwise Operations (CSE 29).
* **Hardware:** Circuit Analysis, KCL/KVL (ECE 35).
