# Project 1: Interrupt-Driven LED State Machine (FSM)

## Overview
This project implements a responsive, non-blocking I/O system using **Hardware Interrupts (EXTI)** and a **Finite State Machine (FSM)**. Unlike traditional polling methods that waste CPU cycles, this driver leverages the STM32's **NVIC** to handle user inputs asynchronously.

## Features
* **Event-Driven:** Uses `EXTI15_10` to detect button presses (Falling Edge) on PC13.
* **Hardware Interrupts:** Configured **NVIC** (Nested Vectored Interrupt Controller) to manage IRQ priority and execution.
* **Finite State Machine:** Toggles between 3 modes: `OFF` -> `SOLID ON` -> `BLINK` -> `OFF`.
* **Software Debouncing:** Implemented logic in ISR to filter mechanical switch noise.
* **Bare-Metal:** No HAL libraries used. All registers (RCC, GPIO, SYSCFG, EXTI, NVIC) are configured via direct memory access.

## Hardware Setup
* **Board:** STM32 Nucleo-F446RE
* **User Button:** Connected to **PC13** (Built-in)
* **User LED:** Connected to **PA5** (Built-in)

## How It Works
1.  **Initialization:** The `GPIO_Init` function configures PA5 as Output and PC13 as IT_FT (Interrupt Falling Edge).
2.  **Interrupt Handling:** When the button is pressed, the CPU jumps to `EXTI15_10_IRQHandler`.
3.  **State Transition:** The ISR updates the global `g_LedState` variable.
4.  **Main Loop:** The while(1) loop continuously polls the state variable (updated asynchronously by the ISR) to execute the corresponding LED pattern.
