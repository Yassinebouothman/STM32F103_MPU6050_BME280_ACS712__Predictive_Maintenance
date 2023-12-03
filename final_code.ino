#include "final_code.h"

void setup() {

  Serial.begin(9600);

  // Writing to MPU6050 I2C
  WritingToMPU_I2C();

  // Starting bme I2C
  bme.begin(BME_addr);

  // Starting MPU I2C
  MPU_I2C_START();
  
  // change accelerometer sensitivity : 0x00 for 2g, 0x08 for 4g, 0x10 for 8g, 0x18 for 16g
  change_MPU_sensitivity();  
  }

void loop() {
  // Reading MPU6050 values
  readingAccelerometerValues();
  
  // Reading BME280 temperature values
  readingTemperatureValues();
  
  // Reading ACS712 current values
  readingCurrentValues();

  // Writing data via uart serial communication
  sendDataViaUart();

  delay(3000);
}
