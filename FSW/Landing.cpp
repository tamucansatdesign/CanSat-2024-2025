#include "Common.h"
#include "Hardware.h"
#include "States.h"

namespace States
{    
  void Landing()
  { 
    Hardware::processCommands(1,1,1,1,1);
    Hardware::read_gps();
    Hardware::read_sensors();
    
    // State -> Recovery if altitude << 2m
    if(Hardware::sensor_data.altitude < 2){
      EE_STATE = 4;
    }

    
    
  }
}