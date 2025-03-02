#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>

// update the serial wire values to match actual configuration
#define GPS_SERIAL Serial7
#define GROUND_XBEE_SERIAL Serial8
#define BMP_WIRE (&Wire2)
#define BNO_WIRE (&Wire2)

// Header containing all constants and hardware identities
namespace Common
{
  const int SERIAL_BAUD = 115200; // Serial communication rate in bit/s
  const int I2C_CLOCK_SPEED = 400000; // I2C clock speed in Hz

  const float SEA_LEVEL = 1014.6f;
  const uint16_t TEAM_ID = 2054;
  const unsigned long TELEMETRY_DELAY = 1000; // 1 Hz

  const byte VOLTAGE_PIN = 48;      // Teensy 4.1 VIN pin
  const byte HS_SERVO_PIN = 45;     // Servo 1 PWM pin
  const byte PARA_SERVO_PIN = 44;   // Servo 2 PWM pin
  const byte CAMERA_PIN = 5;        // Camera 1 trigger pin
  const byte BONUS_CAMERA_PIN = 6;  // Camera 2 trigger pin
  const byte ENCODER_PIN1=5, ENCODER_PIN2 = 6; //encoder pins
  const byte AUDIO_BEACON_PIN = 8;  // Audio buzzer signal pin

  // Variable addresses for EEPROM reading and writing
  const uint16_t BP_ADDR = 0;  // base (ground-level) pressure used for calibration ; address space: 0-4 (float = 4 bytes)
  const uint16_t PC_ADDR = 4;  // packet count                                      ; address space: 4-6 (uint16_t = 2 bytes)
  const uint16_t ST_ADDR = 6;  // states                                            ; address space: 6-8 (uint16_t = 2 bytes)
  
  // struct CanSat_States
  // {

  //   char HS_DEPLOYED; // heat shield deployment: deployed -> 'P' ; else 'N'
  //   char HS_RELEASED; // heat shield released: released -> 'R' ; else 'N'
  //   char PC_DEPLOYED; // parachute deployment: deployed -> 'C' ; else 'N'
  // };

  struct Sensor_Data
  {
    float vbat; // Teensy voltage sensor
    float altitude; // BMP388: pressure-calculated altitude
    float temperature; // BMP388
    float pressure; // BMP388
    float gyro_r; // BNO 085: tilt in X (roll)
    float gyro_y; // BNO 085: rotation speed around Y
    float gyro_z; // BNO 085: rotation speed around Z
    float accel_r; // BNO 085: accel in X (roll)
    float accel_y; // BNO 085: accel in Y (pitch)
    float accel_z; // BNO 085: accel in Z (yaw)
    float mag_x; // BNO 085: magnetic field in X
    float mag_y; // BNO 085: magnetic field in Y
    float mag_z; // BNO 085: magnetic field in Z
    float auto_gyro_speed; // auto gyro rotation speed
  };

  struct GPS_Data
  {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;
    float latitude; 
    float longitude;
    float altitude;
    byte sats;
  };
  
}

#endif