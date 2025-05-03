// ESP32 Input Simulator for STM32 Test Cases

// ADC output pin (via DAC)
#define ADC_SIM_PIN 25   // GPIO25 = DAC1

// USARTs to STM32
#define USART0_TX 1     // Serial0 TX → STM32 USART1 RX
#define USART2_TX 17      // Serial2 TX → STM32 USART2 RX

void setup() {
  // Setup DAC output
  pinMode(ADC_SIM_PIN, OUTPUT);

  // USARTs to STM32
  Serial1.begin(115200, SERIAL_8N1, -1, USART2_TX); // STM32 USART2 RX
  Serial2.begin(115200, SERIAL_8N1, -1, USART0_TX); // STM32 USART1 RX

  delay(2000);  // Allow STM32 to boot first
}

void loop() {
  Serial.println("Running test sequence...");
  //simulateADCVoltage(84);    // ~1.1V


  // ===== 1. ADC Simulation =====
  simulateADCVoltage(84);    // ~1.1V
  delay(1000);
  //simulateADCVoltage(127);   // ~1.65V
  //delay(1000);
  //simulateADCVoltage(255);   // ~3.3V
  //delay(1000);




  // ===== 2. USART1 Data Test =====
  //sendUSART1ValidData(0x00, 0x00);
  //delay(1000);//
  sendUSART1ValidData(0x0F, 0x00);
  delay(1000);

  /*
  sendUSART1MalformedData();
  delay(1000);
*/
  // ===== 3. USART2 Float Input =====
  sendUSART2Float(10.5f);  // Valid
  delay(1000);
  //sendUSART2Float(0.5f);   // Should clamp to 1ms
  //delay(1000);
  //sendUSART2Float(-1.0f);     // Should trigger watchdog
  //delay(2000);

}

void simulateADCVoltage(uint8_t dacValue) {
  dacWrite(ADC_SIM_PIN, dacValue);
  Serial.printf("Set DAC to %u (approx %.2f V)\n", dacValue, (3.3 * dacValue) / 255.0);
}

void sendUSART1ValidData(uint8_t MSB, uint8_t LSB) {
  Serial2.write(MSB);
  Serial2.write(LSB);
  Serial.println("Sent USART1 valid packet: A5 3C");
}

void sendUSART1MalformedData() {
  Serial2.write('Z');  // Unexpected character
  Serial2.write(0x01); // Short packet
  Serial.println("Sent USART1 malformed data");
}

void sendUSART2Float(float value) {
  Serial1.write((uint8_t*)&value, sizeof(float));  // Send 4 bytes as-is
}

