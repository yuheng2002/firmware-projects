# Firmware Projects (Planned for Winter Break 2025)
These projects are planned for completion during the 2025 winter break to strengthen my C programming and embedded firmware fundamentals.

# 1. PWM Fan Speed Controller (Planned)

Platform: STM32 Nucleo or Arduino
Focus: C programming, ADC, PWM, firmware debugging

Description:
A temperature-controlled fan system that reads analog temperature values through the ADC and adjusts fan speed using PWM. Modes (Low/Medium/High) will be selected based on temperature thresholds. Serial output will be used for monitoring and debugging.

Planned Skills:
- ADC reading & signal mapping
- PWM configuration
- Basic control logic & state handling
- Debugging firmware behavior via serial prints

# 2. Interrupt-Driven LED Controller (Planned)

Platform: STM32 Nucleo or Arduino
Focus: GPIO interrupts, debouncing, state machines

Description:
- A button-controlled LED system where each button press cycles the LED through multiple modes (off, solid, blink, breathe). Input noise from the button will be handled through software debouncing. LED behavior will be implemented using a simple state machine.

Planned Skills:
- GPIO interrupt setup
- Debouncing algorithm
- ISR (Interrupt Service Routine) structure
- Timing control for LED patterns

# Goals
- Strengthen low-level C programming
- Build experience with MCU peripherals (GPIO, ADC, PWM, interrupts)
- Practice debugging and structured firmware design
- Prepare for embedded/firmware internship interviews
