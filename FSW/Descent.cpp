#include "Common.h"
#include "Hardware.h"
#include "States.h"

namespace States
{    
  void Descent()
  { 
    States::processCommands(1,1,1,1,1);
    Hardware::read_gps();
    Hardware::read_sensors();

    // State -> Landing: if airspeed < 1 m/s and altitude << 2m
    if ( Hardware::sensor_data.altitude < 2) {
      EE_STATE = 5;
      // TODO: EEPROM.put(Common::ST_ADDR, EE_STATE);
    }

    // Transmit 1 Hz telemetry
    if (Hardware::CX) {
      String packet = States::build_packet("Descent");
      Serial.println(packet);
      Hardware::write_ground_radio(packet);
    }

    if(!States::landing_legs_deployed && Hardware::sensor_data.altitude < 50)
    {
      landing_legs_deployed = true;
      Hardware::landing_leg_1.write(180);
      Hardware::landing_leg_2.write(180);
      Hardware::landing_leg_3.write(180);
    }

    

  }
}