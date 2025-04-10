#include "Hardware.h"
#include "States.h"

namespace States
{    
  void StartDescent()
  { 
    Hardware::processCommands(1,1,1,1,1);
    Hardware::read_gps();
    Hardware::read_sensors();

      // State -> Descent: if sim mode then altitude decreases if velocity changes sign or altitude decreases
    if (Hardware::sensor_data.altitude > .75 * Hardware::peak_altitude) {
      EE_STATE = 3;
      // TODO: EEPROM.put(Common::ST_ADDR, EE_STATE);
    }
    
    // Transmit 1 Hz telemetry
    if (Hardware::CX) {
      String packet = Hardware::build_packet("StartDescent");
      Serial.println(packet);
      Hardware::write_ground_radio(packet);
    }

    

    

  }
}