#include "final_code.h"

void readingTemperatureValues()
{
  temperature = bme.readTemperature();
}

void readingCurrentValues()
{
  current = ACS.mA_DC()/1000;
}

void WritingToMPU_I2C()
{
  WIRE1.beginTransmission(MPU_addr);
  WIRE1.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  WIRE1.endTransmission(false);
  WIRE1.requestFrom(MPU_addr, 6, true); // I used 6 registers because I need only accelerometer values for my application
}

void readingAccelerometerValues()
{
  // Reading accelerometer values
  AcX = WIRE1.read() << 8 | WIRE1.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = WIRE1.read() << 8 | WIRE1.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = WIRE1.read() << 8 | WIRE1.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Calculate displacement (assuming constant acceleration)
  //displacement += 0.5 * (AcX / 16384.0) * pow(1 / 0.05, 2); // 1/0.05 is the sampling rate in seconds

  // Calculate RMS of acceleration
  rms_vibration = sqrt(pow(AcX / 16384.0, 2) + pow(AcY / 16384.0, 2) + pow(AcZ / 16384.0, 2));
}

void readingGyroscopeValues()
{
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}


void sendDataViaUart()
{
  byte* p1 = (byte*) &temperature;  // Putting the temperature value in a Byte pointer
    for (int i = 0; i < 4; i++) 
    {
      Serial.write(p1[i]);
    }
  byte* p2 = (byte*) &rms_vibration;
    for (int j = 0; j < 4; j++) 
    {
      Serial.write(p2[j]);
    }
  byte* p3 = (byte*) &current;
    for (int k = 0; k < 4; k++)
    {
      Serial.write(p3[k]);
    }
}

void MPU_I2C_START()
{
  WIRE1.begin(MPU_addr); 
  WIRE1.beginTransmission(MPU_addr);
  WIRE1.write(0x6B); // PWR_MGMT_1 register
  WIRE1.write(0x00);    // set to zero (wakes up the MPU6050)
  WIRE1.endTransmission(true);
}

void change_MPU_sensitivity()
{
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x1C);                // Send accelerometer configuration register
  Wire.write(0x18);                // Set full-scale range for accelerometer to ±16g
  Wire.endTransmission(true);
}
