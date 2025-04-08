#pragma once
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "Common.h"

#include <Wire.h>             // I2C protocol
#include <Adafruit_BMP3XX.h>  // BMP388 
#include <Adafruit_BNO08x.h>  // BNO085 
#include <Adafruit_GPS.h>     // GPS
#include <TeensyThreads.h>    // Multithreading
#include <EEPROM.h>
#include <Servo.h>
#include <Encoder.h>
#include <SD.h>
#include <deque>

// Covers initialization of sensors/radios, and any functions that utilize this hardware
namespace Hardware
{
  extern bool SIM_ENABLE;                      // SIM ENABLE -> true ; SIM DISABLE -> false
  extern bool SIM_ACTIVATE;                    // SIM ENABLE and SIM ACTIVATE -> true ; SIM DISABLE -> false
  extern int SIM_PRESSURE;
  extern float peak_altitude;
  
  extern unsigned long current_time;
  extern unsigned long previous_time;

  extern bool CX;                              // CX on -> true ; CX off -> false

  // Variables preceded by "EE_" are values that write/read from EEPROM
  extern float EE_BASE_PRESSURE;               // CAL -> base_pressure ; else -> -1
  extern uint16_t EE_PACKET_COUNT;

  extern int lastCheck;
  extern String lastCMD;

  const int chipSelect = BUILTIN_SDCARD;
  static File telemetry;

  extern Adafruit_BMP3XX bmp;
  extern Adafruit_BNO08x bno;
  extern Encoder enc;
  extern Adafruit_GPS gps;
  extern class Camera nosecone_cam;
  extern class Camera auto_gyro_cam;
  extern Servo leg1;
  extern Servo leg2;
  extern Servo leg3;
  extern Servo reactionWheel; //change to DC motor later

//add mutex's
  extern Threads::Mutex general_mtx; //shared resources: SIM_ACTIVATE, SIM_ENABLE, SIM_PRESSURE, CX, EE_BASE_PRESSURE, EE_PACKET_COUNT, lastCMD
  //used in:
    //read_sensors
    //build_packet
  extern Threads::Mutex gps_mtx; //gps, gps_data, GPS_SERIAL
  //used in:
    //read_gps
    //processCommands
    //build_packet
  extern Threads::Mutex radio_mtx; //XBEE, GROUND_XBEE_SERIAL, telemetry
  //used in:
    //write_ground_radio
    //read_ground_radio
  extern Threads::Mutex sensor_mtx; //BMP388, BNO085, rotary encoder, enc, sensor_data
  //used in:
    //read_sensors
    //build_packet
  extern Common::Sensor_Data sensor_data;
  extern Common::GPS_Data gps_data;
  
  void init();

  // Teensy 4.1, BMP388, BNO085, and rotary encoder sensors operation
  void setup_BMP();
  void setup_BNO();
  void setup_RE();
  void read_sensors();

  // Ultimate GPS Breakout operation
  void setup_GPS();
  void read_gps();
    
  // XBee Pro S2C operation
  void setup_XBee();
  void write_ground_radio(const String &data);
  bool read_ground_radio(String &data);

  // Buzzer operation
  void buzzer_on();
  void buzzer_off();

  //Nichrome wire
  //void nichrome_burn();

  //Process Commands
  void processCommands(const bool enableCX, const bool enableST, const bool enableSIM, const bool enableCAL, const bool enableMEC);
  String build_packet(String state);
  // Camera operation
  class Camera 
  {
    public: 
      Camera(const byte camera_pin);
      void update_camera(bool record);
      bool is_recording();

    private:
      const byte camera_pin;
      elapsedMillis cameraHold;
      bool cameraRecording;
      bool firstCameraCall;

      void start_recording();
      void stop_recording();
  };

}

#endif