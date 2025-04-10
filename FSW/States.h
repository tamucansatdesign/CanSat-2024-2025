#pragma once
#ifndef __STATES_H__
#define __STATES_H__

// State logic
namespace States
{
  extern uint16_t EE_STATE;
  extern bool landing_legs_deployed;
  
  // ordered by state diagram (2024-2025: State diagram was unofficially revised)
  // void setup() : Bootup -> EE_STATE = 0
    // Initialize hardware
    // Update recovery parameters with EEPROM
    // Sync up RTC with GPS
    // Start Kalman filtering
    // Transmit 1 Hz telemetry
  void Ascent();                                            // Ascent -> EE_STATE = 2

    // Reached peak altitude: 
      // State -> Descent: if sim mode then altitude decreases   if velocity changes sign or altitude decreases
      // Transmit 1 Hz telemetry
      // Kalman Filter
      // Start recording of nosecone camera
      // Start Reaction Wheel Control system
  void StartDescent();    // StartDescent -> EE_STATE = 3
  
  //Transmit
  // Kalman Filter
  //nichrome wire burn
  //start gyro camera
  //State -> 75% peak altitude
  //Reaction wheel control system
  void PayloadRelease(); // Descent -> EE_STATE = 4
    // Altitude 100m:
      // State -> Landing: if airspeed < 1 m/s and altitude << 2m
      // Deploy parachute
      // Move landing legs to landing deployment
  void Landing();         // Landing -> EE_STATE = 5

    // Cease telemetry
    // Stop both camera recordings
    // Activate audio beacon
  void Recovery();       // Recovery -> EE_STATE = 6
  

};

#endif  