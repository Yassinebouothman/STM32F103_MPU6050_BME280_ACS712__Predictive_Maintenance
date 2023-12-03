#ifndef FINAL_CODE_H
#define FINAL_CODE_H
#include <Wire.h>
#include <math.h>
#include <Adafruit_BME280.h>
#include <ACS712.h>
#include <Arduino.h>

// Configuring I2C ports
TwoWire WIRE = TwoWire(1, I2C_FAST_MODE);
TwoWire WIRE1 = TwoWire(2, I2C_FAST_MODE);

#define MPU_addr 0x68
#define BME_addr 0x76
#define WIRE Wire

//Defining variables
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
//float displacement = 0.0; // displacement in meters
float rms_vibration = 0.0; // root mean square of acceleration
float temperature, current;

// Creating objects
Adafruit_BME280 bme;
ACS712  ACS(PA1, 3.3, 4095, 185);

// Functions initialisations
void readingTemperatureValues();
void readingCurrentValues();
void WritingToMPU_I2C();
void readingAccelerometerValues();
void readingGyroscopeValues();
void sendDataViaUart();
void MPU_I2C_START();
void change_MPU_sensitivity();

#endif
