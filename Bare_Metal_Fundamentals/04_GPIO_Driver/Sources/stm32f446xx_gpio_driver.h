/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: 2025/12/23
 *      Author: Yuheng
 */

#ifndef SOURCES_STM32F446XX_GPIO_DRIVER_H_
#define SOURCES_STM32F446XX_GPIO_DRIVER_H_

#include <stdint.h>

/*
 * ==========================================
 * 1. Generic Macros
 * ==========================================
 * Standardizing logic states to improve readability.
 * Instead of passing '1' or '0', we pass 'ENABLE' or 'DISABLE'.
 */
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET

/*
 * ==========================================
 * 2. GPIO Register Definition Structure
 * ==========================================
 * Note on Logic:
 * We do not manually define offsets (e.g., +0x04).
 * Since C struct members are stored sequentially in memory and
 * uint32_t occupies exactly 4 bytes, the compiler automatically
 * aligns these members to the hardware offsets (0x00, 0x04, 0x08...)
 * relative to the base address.
 */
typedef struct{
	volatile uint32_t MODER;    // Mode Register: Configures the pin direction (Input, Output, etc.)
	volatile uint32_t OTYPER;   // Output Type: Chooses between Push-Pull (strong drive) or Open-Drain.
	volatile uint32_t OSPEEDR;  // Output Speed: Determines how fast the pin can toggle states (slew rate).
	volatile uint32_t PUPDR;    // Pull-up/Pull-down: internal resistors to stabilize floating pins.
	volatile uint32_t IDR;      // Input Data: Read this to get the current signal level on the pin.
	volatile uint32_t ODR;      // Output Data: Write to this to set the pin level (High/Low).
	volatile uint32_t BSRR;     // Bit Set/Reset: Atomic way to set/reset pins (safer than ODR in interrupts).
	volatile uint32_t LCKR;     // Lock Register: Freezes the configuration to prevent accidental changes.
	volatile uint32_t AFR[2]; // Offset: 0x20
							  // AFR[0] is AFRL (Offset 0x20) for pins 0-7
							  // AFR[1] is AFRH (Offset 0x24) for pins 8-15
} GPIO_RegDef_t;

/*
 * ==========================================
 * 3. Peripheral Base Addresses
 * ==========================================
 * Fixed physical addresses from the STM32F446 Reference Manual (Memory Map).
 * The GPIO ports hang off the AHB1 Bus.
 */
#define GPIOA_BASEADDR      (0x40020000U)
#define GPIOB_BASEADDR      (0x40020400U)
#define GPIOC_BASEADDR      (0x40020800U)
#define GPIOD_BASEADDR      (0x40020C00U)
#define GPIOE_BASEADDR      (0x40021000U)
#define GPIOF_BASEADDR      (0x40021400U)
#define GPIOG_BASEADDR      (0x40021800U)
#define GPIOH_BASEADDR      (0x40021C00U)

/*
 * RCC (Reset and Clock Control) Base Address.
 * We need this address to enable the clock for the GPIO peripherals.
 * Without enabling the clock in the RCC registers, GPIOs remain dead (powered down).
 */
#define RCC_BASEADDR        (0x40023800U)

/*
 * ==========================================
 * 4. GPIO Port Macros (Typecasting)
 * ==========================================
 * Converts the raw address (uint32_t) into a pointer to our structure.
 * This acts as the "key" to access the hardware.
 * Usage: GPIOA->MODER = ...
 */
#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG   ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*)GPIOH_BASEADDR)

/*
 * ==========================================
 * 5. Clock Enable Macros
 * ==========================================
 * These macros toggle specific bits in the RCC_AHB1ENR register.
 * Logic: Base ADDR of RCC + Offset of AHB1ENR (0x30).
 * Bit 0 = GPIOA, Bit 1 = GPIOB, etc.
 */
#define GPIOA_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 0) )
#define GPIOB_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 1) )
#define GPIOC_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 2) )
#define GPIOD_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 3) )
#define GPIOE_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 4) )
#define GPIOF_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 5) )
#define GPIOG_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 6) )
#define GPIOH_PCLK_EN()     ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) |= (1 << 7) )

/*
 * ==========================================
 * 6. Clock Disable Macros
 * ==========================================
 * These macros disable specific bits in the RCC_AHB1ENR register.
 * Logic: Base ADDR of RCC + Offset of AHB1ENR (0x30).
 * Bit 0 = GPIOA, Bit 1 = GPIOB, etc.
 * set to 0 -> disabled
 */
#define GPIOA_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 0) )
#define GPIOB_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 1) )
#define GPIOC_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 2) )
#define GPIOD_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 3) )
#define GPIOE_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 4) )
#define GPIOF_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 5) )
#define GPIOG_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 6) )
#define GPIOH_PCLK_DIS()    ( *(volatile uint32_t*)(RCC_BASEADDR + 0x30) &= ~(1 << 7) )

/*
 * ==========================================
 * 7. Configuration Structures
 * ==========================================
 */

/*
 * GPIO Pin Configuration Settings
 * This acts as a "Menu" or "Form" for the user.
 * Before initializing, the user fills this out to specify exactly
 * how a single pin should behave.
 */
typedef struct{
	uint8_t GPIO_PinNumber;         // Possible values: 0-15
	uint8_t GPIO_PinMode;           // Possible values: @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;          // Possible values: @GPIO_PIN_SPEED
	uint8_t GPIO_PinPuPdControl;    // Possible values: @GPIO_PIN_PULL_UP_DOWN
	uint8_t GPIO_PinOPType;         // Possible values: @GPIO_PIN_OUTPUT_TYPES
	uint8_t GPIO_PinAltFunMode;     // Possible values: 0-15 (Only applicable if Mode == AltFn)
} GPIO_PinConfig_t;

/*
 * GPIO Handle Structure
 * This acts as the "Job Order".
 * It bundles the "Where" (pGPIOx base address) and the "How" (PinConfig).
 * We pass this single object to functions like GPIO_Init().
 */
typedef struct{
	GPIO_RegDef_t *pGPIOx;           // Pointer to the GPIO Port Base Address
	GPIO_PinConfig_t GPIO_PinConfig; // The configuration settings for the specific pin
} GPIO_Handle_t;


/*
 * ==========================================
 * 8. Configuration Macros
 * ==========================================
 * Macros to prevent user errors (magic numbers).
 */

/* @GPIO_PIN_MODES */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTN 		2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT 	4 	// Interrupt Falling Edge
#define GPIO_MODE_IT_RT 	5 	// Interrupt Rising Edge
#define GPIO_MODE_IT_RFT 	6 	// Interrupt Rising & Falling Edge

/* @GPIO_PIN_OUTPUT_TYPES */
#define GPIO_OP_TYPE_PP 	0 	// Push Pull (Default)
#define GPIO_OP_TYPE_OD 	1 	// Open Drain (Used for I2C)

/* @GPIO_PIN_SPEED */
#define GPIO_SPEED_LOW 			0
#define GPIO_SPEED_MEDIUM 		1
#define GPIO_SPEED_HIGH 		2
#define GPIO_SPEED_VERY_HIGH 	3

/* @GPIO_PIN_PULL_UP_DOWN */
#define GPIO_NO_PUPD 		0   // No Pull-up/Pull-down (Floating)
#define GPIO_PIN_PU 		1   // Pull-up resistor enabled
#define GPIO_PIN_PD 		2   // Pull-down resistor enabled

/* ==========================================
 * 9. AHB1 Bus Reset Macros
 * RCC AHB1 Peripheral Reset Register (RCC_AHB1RSTR)
 * offset: 0x10
 * 0 -> does not reset IO port x
 * 1 -> resets IO port x
 * RCC_BASEADDR + offset
 * bits 0-7 -> GPIOA-H
 *
 * Core Logic:
 * 1. Set bit to 1 (Assert Reset) -> Reset button is pressed
 * 2. Set bit to 0 (Clear Reset) -> Release the reset button (the user has to let go at some point)
 * ==========================================
 */
#define RCC_AHB1_RESET_OFFSET 0x10
#define RCC_AHB1RSTR_ADDR  ((volatile uint32_t*)(RCC_BASEADDR + RCC_AHB1_RESET_OFFSET))
void GPIOA_REG_RESET(void);
void GPIOB_REG_RESET(void);
void GPIOC_REG_RESET(void);
void GPIOD_REG_RESET(void);
void GPIOE_REG_RESET(void);
void GPIOF_REG_RESET(void);
void GPIOG_REG_RESET(void);
void GPIOH_REG_RESET(void);

/*
 * ==========================================
 * 10. API Function Prototypes
 * ==========================================
 * These are the services offered by the driver.
 */

/*
 * Peripheral Clock Setup
 * Must be called FIRST before using any GPIO Port.
 * 'EnableOrDisable' should be ENABLE or DISABLE macros.
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnableOrDisable);

/*
 * Initialization and De-Initialization
 * GPIO_Init takes the Handle structure to configure settings.
 * GPIO_DeInit resets the port to its default state.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data Read and Write
 * Reading from Input Pin: returns 0 or 1.
 * Reading from Input Port: returns the 16-bit value of the whole port.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

/*
 * Writing to Output Pin: sets a specific pin to 0 or 1.
 * Writing to Output Port: writes to the entire port at once.
 * Toggle: flips the state of the pin (0->1 or 1->0).
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* SOURCES_STM32F446XX_GPIO_DRIVER_H_ */
