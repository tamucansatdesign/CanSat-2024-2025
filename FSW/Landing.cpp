#include "Common.h"
#include "Hardware.h"
#include "States.h"

namespace States
{    
  void Landing()
  { 
    States::processCommands(1,1,1,1,1);
    Hardware::read_gps();
    Hardware::read_sensors();

    // Cease telemetry
    Hardware::CX = false;

    // Stop both camera recordings
    Hardware::nosecone_cam.update_camera(false);
    Hardware::north_cam.update_camera(false);
    
    // Activate audio beacon
    Hardware::buzzer_on();
    
  }
}