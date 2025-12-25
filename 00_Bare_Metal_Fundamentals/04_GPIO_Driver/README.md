# 04_GPIO_Driver (Bare Metal)

## Overview
This project represents a complete refactor of the GPIO control logic on the STM32F446RE (Nucleo-64), moving from direct register manipulation to a **modular driver architecture**. 

This is a pure **Bare Metal** implementation that completely bypasses the HAL library. The goal was not just to blink an LED, but to build a scalable, readable hardware abstraction layer from scratch.

## Key Achievements & Features

* **Modular Architecture (No More Hardcoding)** Refactored the logic to use `GPIO_RegDef_t` and `GPIO_Handle_t` structs. This maps the hardware memory blocks cleanly, eliminating the need to look up and hardcode raw addresses like `0x4002...` manually.

* **Driver Core APIs** Implemented essential driver APIs with clear separation of concerns:
    * `GPIO_Init`: Handles initialization logic.
    * `GPIO_Read` / `GPIO_Write`: Standardized I/O operations.
    * `GPIO_Toggle`: Simplified state inversion.

* **Readable Macros (Bye-bye Magic Numbers)** Replaced confusing magic numbers (e.g., `0x00`, `0x01`) with readable bit-shifting macros and clock control definitions defined in the header. The code is now self-documenting.

* **Verification** The driver is verified in `main.c`: Toggling the User LED (PA5) using the User Button (PC13) proves the driver's read/write capabilities work as expected.

## File Structure
* `stm32f446xx_gpio_driver.h`: Register definitions, macros, and API prototypes (The "Brain").
* `stm32f446xx_gpio_driver.c`: Implementation of the API logic (The "Body").
* `main.c`: Application layer to test the driver (The "Proof").

## How to Build
1.  Open the project in STM32CubeIDE.
2.  Ensure your `CMakeLists.txt` or IDE paths include the driver source files.
3.  Build and Run on the NUCLEO-F446RE board.
