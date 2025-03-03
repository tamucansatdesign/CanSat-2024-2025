#include "Common.h"
#include "Hardware.h"
#include "States.h"

namespace States
{  
  uint16_t EE_STATE = 0;
  
  void Standby()
  { 
    States::processCommands(1,1,1,1,0);
    Hardware::read_gps();
    Hardware::read_sensors();

    // State -> Ascent: if altitude >> 2m
    if (Hardware::sensor_data.altitude > 2) {
      EE_STATE = 2;
      // TODO: EEPROM.put(Common::ST_ADDR, EE_STATE);
    }
    
    // Transmit 1 Hz telemetry
    if (Hardware::CX) {
      String packet = States::build_packet("Standby", cansat_states);
      Serial.println(packet);
      Hardware::write_ground_radio(packet);
    }

    // Start recording of main camera (horizontal view)
    Hardware::nosecone_cam.update_camera(true);
    
    
    
  }
}