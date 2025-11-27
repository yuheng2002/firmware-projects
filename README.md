# Embedded Firmware Learning Journey

This repository documents my self-study projects in **Bare-Metal Embedded C** programming using the **STM32 (ARM Cortex-M)** platform. 

My goal for Winter 2025 is to bridge the gap between my software coursework (CSE 29) and hardware fundamentals (ECE 35) by building low-level drivers from scratch, without relying on high-level libraries like Arduino or HAL.

## 🚧 Planned Projects (Winter 2025)

### Project 1: PWM Fan Controller
**Concept:** A temperature-regulated cooling system.
**Learning Objectives:**
* **Hardware Interfacing:** Connect a temperature sensor via **I2C** protocol.
* **Register Manipulation:** Manually configure **Hardware Timers** to generate **PWM** signals for fan speed control.
* **Logic:** Map temperature readings to fan duty cycles using C.

### Project 2: Interrupt-Driven LED System
**Concept:** A responsive LED control system that handles user input without freezing the CPU.
**Learning Objectives:**
* **Interrupts vs. Polling:** Implement **Hardware Interrupts (ISR)** to handle button presses immediately.
* **State Machine:** Design a Finite State Machine (FSM) in C to toggle between LED modes (Solid, Blink, Breathe).
* **Signal Processing:** Implement software **debouncing** logic to filter out mechanical switch noise.

---

## 🛠 Toolkit
* **Board:** STM32 Nucleo-64
* **Language:** C (Standard C99/C11)
* **Debugging:** GDB & Logic Analyzer (Learning to use)
* **Documentation:** STM32F4 Reference Manual & Datasheets
