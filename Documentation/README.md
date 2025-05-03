# STM32F767ZI Multi-Protocol Controller  
**Firmware for ADC / USART / PWM / I2C / SPI / DAC Integration**


## Hardware Connections

| Peripheral | Pin       | Connection        | Notes                |
|------------|-----------|-------------------|----------------------|
| ADC1       | PA0       | ESP32 DAC         | 0–3.3V analog input   |
| USART1(RX) | PB15      | ESP32 USART TX    | 115200 baud          |
| USART2(RX) | PA3       | ESP32 USART TX    | 115200 baud          |
| PWM (TIM1) | PA8       | Logic Analyzer    | 25kHz output         |
| I2C1       | PB8/PB9   | Logic Analyzer    | 100kHz, addr 0x7C    |
| SPI1       | PA4–PA7   | Logic Analyzer    | 1.9MHz, CS=PG10      |
| DAC1       | PA4       | Multimeter        | 1V offset output     |
| Button     | PC0       | Pull-up           | Active-low           |
| LED        | PC13      | -                 | Overflow indicator   |


## Key Features

### ADC (DMA Mode)
- 12-bit continuous sampling @ 1kHz  
- Stores raw + voltage in `adcData` struct

### Dual USART (DMA + Interrupt)
- **USART1**: 16-bit values for PWM control  
- **USART2**: Floating-point inputs (1–100ms timer control)

### PWM Output (25kHz)
- Duty = ADC + USART1 value  
- Clamped to max 1024

### Protocol Switching Based on Button
- If On board button(trigger) is pressed, I2C stops transmitting and SPI starts sending at a higher prioirty.

### ESP32 Tester
- Accomplishes following operations:
	- Sends test data(adds to ADC value) on USART1
	- Send test data(float value) on USART2
	- Provides required DAC output as input to STM32 as ADC simulation.

### Debugging Tools
1. Logic Analyzer Setup

- SPI: Capture MOSI/SCK/CS (1.9MHz)

- I2C: Decode 0x7C address packets

2. Serial Terminals

- USART1: Send hex values (e.g., A53C)

- USART2: Send floats or F for watchdog test

3. Oscilloscope Checks

- PA8: Verify 25kHz PWM duty cycle

- PC13: 100ms toggle during overflow
