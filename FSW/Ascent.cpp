#include "Hardware.h"
#include "States.h"

namespace States
{    
  void Ascent()
  {

    static float old_velocity = 0.0f;
    Hardware::processCommands(1,1,1,1,1);
    Hardware::read_gps();
    Hardware::read_sensors();
    float velocity = ;
    // State -> altitude >> 2m
    if (Hardware::sensor_data.altitude > 5 && velocity < 0 && Hardware::sensor_data.accel_linear_z < 0) {
      EE_STATE = 2;
      // TODO: EEPROM.put(Common::ST_ADDR, EE_STATE);
    }
    
    if(Hardware::sensor_data.altitude > Hardware::peak_altitude){
      Hardware::peak_altitude = Hardware::sensor_data.altitude;
    }


    // Transmit 1 Hz telemetry
    if (Hardware::CX) {
      String packet = Hardware::build_packet("Ascent");
      Serial.println(packet);
      Hardware::write_ground_radio(packet);
    }


    old_velocity = velocity;
  }
}