#include "Common.h"
#include "Hardware.h"
#include "States.h"


// IMPROVEMENTS:
// when processor resets request update from GSC: lastCMD, cameras operating?
// add multithreading
  // GPS thread
  // Sensor/State diagram thread
  // Telemetry thread (1 Hz)
// BMP388 ground-level calibration

// TODO:
// Fix BNO085 tilt and rotation angles
// Running average to account for spikes
// Test EEPROM values 
// Test mission time and set time command 
// Test audio buzzer 

// void setup() {
//   // Start Serial communication, if debugging
//   Serial.begin(Common::SERIAL_BAUD);
//   Serial.println("Serial Connection Established.");

//   // Initialize all components  
//   Hardware::init();

//   // Hardware::main_cam.update_camera(true);
// }

// void loop() {
//   States::processCommands(1,1,1,1,1);

//   Hardware::read_gps();
//   Hardware::read_sensors();

//   if (Hardware::CX) {
//     String packet = States::build_packet("Test", cansat_states);
//     Serial.println(packet);
//     Hardware::write_ground_radio(packet);
//   }

//   delay(Common::TELEMETRY_DELAY);

//   if (Hardware::SIM_ACTIVATE) {
//     // Hardware::main_cam.update_camera(false);
//     Hardware::buzzer_on();
//     Serial.println("buzzer on");
//   }
//   else {
//     Hardware::buzzer_off();
//     Serial.println("buzzer off");
//   }
// }

void setup() {
  Serial.begin(Common::SERIAL_BAUD);
  Serial.println("Serial Connection Established.");

  // Initialize hardware
  Hardware::init();

  // Update recovery parameters with EEPROM
  EEPROM.get(Common::BP_ADDR, Hardware::EE_BASE_PRESSURE);
  EEPROM.get(Common::PC_ADDR, Hardware::EE_PACKET_COUNT);
  EEPROM.get(Common::ST_ADDR, States::EE_STATE);

  // Sync up RTC with GPS
  // setTime(Hardware::gps_data.hours, Hardware::gps_data.minutes, Hardware::gps_data.seconds, Hardware::gps_data.day, Hardware::gps_data.month, Hardware::gps_data.year);
}

void loop() {
  // Loop through each state 
  switch (States::EE_STATE)
  { 
    
    case 1:
      States::Ascent();
      break;
    case 2:
      States::Descent();
      break;
    case 3:
      States::PayloadRelease();
      break;    
    case 5:
      States::Landing();
      break;
    default:
      States::Standby();
      break;
  }
  delay(Common::TELEMETRY_DELAY);
}