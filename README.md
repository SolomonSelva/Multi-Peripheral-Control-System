## Developed a robust embedded system leveraging 8+ STM32 peripherals with DMA-driven architecture. Key achievements:

# Real-Time Data Pipeline:
- ADC (DMA+IT) + USART1 (DMA) → PWM (25kHz) with dynamic duty control (0-1024)
- USART2 float input → Configurable timer interrupts (1-100ms)

# Multi-Protocol Communication:
- Auto-routed I2C (100kHz @0x7C) / SPI (1.9MHz) based on button state
- Checksum-validated HEX data display via USART2

# Safety-Critical Features:
- Independent Watchdog (2s) with 'F' command failsafe
- PC13 visual alert for overflow conditions (>1024)
- DAC output with 1V hardware-clamped offset
