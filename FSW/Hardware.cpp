#include "Hardware.h"

namespace Hardware
{
  bool SIM_ACTIVATE = false;  
  bool SIM_ENABLE = false;
  int SIM_PRESSURE = 0;
  float peak_altitude = 0;

  bool CX = false;

  unsigned long current_time = 0;
  unsigned long previous_time = 0;


  float EE_BASE_PRESSURE = -1;
  uint16_t EE_PACKET_COUNT = 0;

  String lastCMD = "None";

  Adafruit_BMP3XX bmp;
  Adafruit_BNO08x bno;
  Encoder enc(Common::ENCODER_PIN1, Common::ENCODER_PIN2);
  Adafruit_GPS gps(&GPS_SERIAL);
  
  Camera nosecone_cam(Common::NOSECONE_CAMERA_PIN);
  Camera auto_gyro_cam(Common::AUTO_GYRO_CAMERA_PIN);
  Servo leg1;
  Servo leg2;
  Servo leg3;
  Servo camera_servo;
  Threads::Mutex gps_mtx;
  Threads::Mutex radio_mtx;
  Threads::Mutex sensor_mtx;
  Threads::Mutex general_mtx;
  Common::Sensor_Data sensor_data;
  Common::GPS_Data gps_data;
  
  // Core function of the Boot-up states. 
  // Performs set up for all sensors and other components, and does anything
  // that needs to be done before Standby state can be entered.
  void init()
  {
    Serial.println("\nBeginning Hardware Initialization...");

    // Starting I2C connections
    Serial.println("\nInitializing I2C connections...");
    BMP_WIRE->begin();   // BMP388 
    BMP_WIRE->setClock(Common::I2C_CLOCK_SPEED);
    BNO_WIRE->begin();  // BNO085
    BNO_WIRE->setClock(Common::I2C_CLOCK_SPEED);
    
    Serial.println("Found I2C connections successfully.");

    // Connect servo pins
    leg1.attach(Common::LANDING_LEG_1_PIN);
    leg2.attach(Common::LANDING_LEG_2_PIN);
    leg3.attach(Common::LANDING_LEG_3_PIN);
    camera_servo.attach(Common::CAMERA_SERVO_PIN);
  

    current_time = millis();
      
    
    // SD card initialization
    SD.begin(chipSelect);

    // Call individual hardware setup functions
    setup_BMP();
    setup_BNO();
    setup_RE();
    setup_XBee();
    setup_GPS();

    Serial.println("\nAll Hardware Initialized.\n");
  }

  // Teensy 4.1, BMP388, BNO085, and rotary encoder sensors operation
  void setup_BMP()
  {
    Serial.println("\nInitializing BMP388...");
    
    // Check if BMP388 is connected
    if (!bmp.begin_I2C(0x77, BMP_WIRE)) { // 0x77 is the assigned I2C address for the BMP388
      Serial.println("Could not find BMP388, check wiring! womp womp :(");
      while (1) { delay(10); } // Halt program if BMP388 is not found
    }
    else {
      Serial.println("Found BMP388 successfully.");
    }

    // Misc. BMP388 Initialization - see Adafruit docs for specifics
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  }

  void setup_BNO()
  {
    Serial.println("\nInitializing BNO085...");
    
    // Attempt init of bno I2C connection
    if (!bno.begin_I2C(0x4A, BNO_WIRE)) {
      // I2C connection failed, log error and halt
      Serial.println("Could not find BNO085, check wiring! womp womp :(");
      while (1) { delay(10); }
    }
    else {
      Serial.println("Found BNO085 successfully.");
    }

    // Attempt to setup desired bno reports
    Serial.println("Setting BNO085 desired reports...");
    if (!bno.enableReport(SH2_LINEAR_ACCELERATION, 5000) 
    || !bno.enableReport(SH2_GRYOSCOPE_CALIBRATED, 5000) 
    || !bno.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED, 5000)) {
      Serial.println("Could not enable sensor reports");
    }
    else {
      Serial.println("Set BNO085 desired reports successfully.");
    }
  }



  void read_sensors()   // read data from Teensy, BMP, BNO, and rotary encoder sensors
  {  
    previous_time = current_time;
    


    // read Teensy: vbat (voltage)
    sensor_data.vbat = ((analogRead(Common::VOLTAGE_PIN) / 1023.0) * 4.2) + 0.35;

    // read BMP: pressure, temperature, altitude
    if (bmp.performReading())
    {
      if (SIM_ENABLE && SIM_ACTIVATE) {
        sensor_data.pressure = SIM_PRESSURE;
        sensor_data.altitude = 44330.0 * (1.0 - pow((SIM_PRESSURE / 100.0) / Common::SEA_LEVEL, 0.1903)); // formula is used directly from BMP388 Arduino library instead of readAltitude() to account for simulated pressure instead of true pressure
      }
      else {
        sensor_data.pressure = bmp.pressure;
        sensor_data.temperature = bmp.temperature;

        if (EE_BASE_PRESSURE != -1) { // if pressure calibrated
            sensor_data.altitude = bmp.readAltitude(EE_BASE_PRESSURE);
        }
        else { // if pressure not calibrated
          sensor_data.altitude = bmp.readAltitude(Common::SEA_LEVEL);
        }
      }
    }

    // TODO: read BNO: mag, accel, gyro
    sh2_SensorValue_t sensorValue;
    if (bno.getSensorEvent(&sensorValue)) 
    {
      switch (sensorValue.sensorId)
      {
        case SH2_LINEAR_ACCELERATION:
          sensor_data.accel_linear_z = sensorValue.un.accel.z;

        break;

        case SH2_MAGNETIC_FIELD_CALIBRATED:
          sensor_data.mag_r = sensorValue.un.magnetic.x;
          sensor_data.mag_p = sensorValue.un.magnetic.y;
          sensor_data.mag_y = sensorValue.un.magnetic.z;
        break;

        case SH2_GYROSCOPE_CALIBRATED:
          sensor_data.gyro_r = sensorValue.un.gyroscope.x;
          sensor_data.gyro_p = sensorValue.un.gyroscope.y;
          sensor_data.gyro_y = sensorValue.un.gyroscope.z;
        break;

      }
    }

    // read rotary encoder
    static long oldPosition = -999;  

    long newPosition = enc.read();
    if(newPosition != oldPosition) {
      int stepsPerRevolution = 24;
      int rotations = newPosition / stepsPerRevolution;
      int rotation_speed = rotations * 1000 / (current_time - previous_time); // Calculate rotation speed in RPM
      sensor_data.auto_gyro_speed = rotation_speed;
      oldPosition = newPosition;
    }
    current_time = millis();
  }

  // Ultimate GPS Breakout operation
  void setup_GPS()
  {
    Serial.println("\nInitializing GPS...");

    // Check init of GPS UART connection
    if (!gps.begin(9600)) {
      // UART connection failed, log error and halt
      Serial.println("Could not find GPS, check wiring! womp womp :(");
      while (1) { delay(10); }
    }
    else {
      Serial.println("Found GPS successfully.");
    }

    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    // gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // GPS.sendCommand(PGCMD_ANTENNA);

    // while (1) {
    //   while (!gps.newNMEAreceived())
    //   {
    //     char c = gps.read();
    //   }
    //   gps.parse(gps.lastNMEA());

    //   if (gps.fix) {
    //     Serial.println("GPS fixed onto satellites successfully.");
    //     break;
    //   }
    //   Serial.println("Looking for GPS fix onto satellites...");
    //   delay(5000);
    // }
  }

  void read_gps_loop()
  {
    gps_mtx.lock();
    if(gps.newNMEAreceived())
    {
      if(gps.parse(gps.lastNMEA()))
      {
      //Serial.println(String(gps.hour) + ":" + String(gps.minute) + ":" + String(gps.seconds) + "." + String(gps.milliseconds));
      setTime(gps.hour, gps.minute, gps.seconds, gps.day, gps.month, gps.year);
    

      gps_data.hours = gps.hour;
      gps_data.minutes = gps.minute;
      gps_data.seconds = gps.seconds;
      gps_data.milliseconds = gps.milliseconds;
      gps_data.latitude = gps.latitude;
      gps_data.longitude = gps.longitude;
      gps_data.altitude = gps.altitude;
      gps_data.sats = (byte)(unsigned int)gps.satellites;  // We do this double conversion to avoid signing issues
      }
    }
    gps_mtx.unlock();
  }

  void setup_RE()
  {
    Serial.println("\nInitializing Rotary Encoder...");
    enc = Encoder(Common::ENCODER_PIN1, Common::ENCODER_PIN2);
    pinMode(Common::ENCODER_PIN1, INPUT_PULLUP);
    pinMode(Common::ENCODER_PIN2, INPUT_PULLUP);
    // Check init of rotary encoder connection
    if (digitalRead(Common::ENCODER_PIN1) != HIGH || digitalRead(Common::ENCODER_PIN2) != HIGH) {
        Serial.println("Found Rotary Encoder successfully.");

    }
    else {
      // UART connection failed, log error and halt

      Serial.println("Could not find Rotary Encoder, check wiring! womp womp :(");
      while (1) { delay(10); }
    }
  }



  // XBee Pro S2C operation
  void setup_XBee() 
  {
    Serial.println("\nInitializing XBee...");

    GROUND_XBEE_SERIAL.begin(Common::SERIAL_BAUD);

    // Check init of XBee UART connection
    if (!GROUND_XBEE_SERIAL) {
      // UART connection failed, log error and halt
      Serial.println("Could not find XBee, check wiring! womp womp :(");
      while (1) { delay(10); }
    }
    else {
      Serial.println("Found XBee successfully.");
    }
  }

  void write_ground_radio(const String &data) 
  {
    // write_mutex.lock();
    GROUND_XBEE_SERIAL.println(data);
    // write_mutex.unlock();

    telemetry = SD.open("Flight_3181.csv", FILE_WRITE);
    telemetry.println(data);
    telemetry.close();

    
  }

  bool read_ground_radio(String &data)
  {
    String buffer = "";  // Buffer to hold incoming data

    while (GROUND_XBEE_SERIAL.available())
    {
        char c = GROUND_XBEE_SERIAL.read();
        buffer += c;

        // Check for the end of a message
        if (c == '\n' && buffer.endsWith("\r\n"))
        {
            // Remove the delimiter from the buffer and return the message
            data = buffer.substring(0, buffer.length() - 2);  // Remove \r\n
            return true;
        }
    }

    // No complete message received yet
    return false;
  }

  // Buzzer operation 
  void buzzer_on()
  {
    analogWriteFrequency(Common::AUDIO_BEACON_PIN, 4000);
    analogWrite(Common::AUDIO_BEACON_PIN, 128);
  }

  void buzzer_off()
  {
    analogWriteFrequency(Common::AUDIO_BEACON_PIN, 0);
    analogWrite(Common::AUDIO_BEACON_PIN, 0);
  }

  // Camera operation
  Camera::Camera(const byte camera_pin) : camera_pin(camera_pin), cameraHold(0), cameraRecording(false), firstCameraCall(true) {}

  void Camera::update_camera(bool record)
  {
      if (record && !cameraRecording)
      {
        if (firstCameraCall)
        {
            cameraHold = 0;
            firstCameraCall = false;
        }
        start_recording();
      } 
      else if (!record && cameraRecording)
      {
        if (firstCameraCall)
        {
            cameraHold = 0;
            firstCameraCall = false;
        }
        stop_recording();
      }
  }

  bool Camera::is_recording()
  {
    return cameraRecording;
  }

  void Camera::start_recording()
  {
      if (cameraHold < 150)
      {
        digitalWrite(camera_pin, LOW);
      } 
      else
      {
        digitalWrite(camera_pin, HIGH);
        cameraRecording = true;
        firstCameraCall = true;
      }
  }

  void Camera::stop_recording()
  {
      if (cameraHold < 550)
      {
        digitalWrite(camera_pin, LOW);
      }
      else
      {
        digitalWrite(camera_pin, HIGH);
        cameraRecording = false;
        firstCameraCall = true;
      }
  }
  // helper functions
  void processCommands(const bool enableCX, const bool enableST, const bool enableSIM, const bool enableCAL, const bool enableMEC)
  {
    String received;
    if (Hardware::read_ground_radio(received)) 
    {
      // remove whitespace and commas from received string
      received.trim();
      received.replace(",", "");

      // check if command sent with proper team id
      if (received.startsWith("CMD" + String(Common::TEAM_ID))) 
      {
        String cmd = received.substring(7,received.length());
        Hardware::lastCMD = cmd;
        Serial.println(cmd);

        // CMD,<TEAM_ID>,CX,ON|OFF
        if (enableCX && cmd.startsWith("CX")) 
        {
          if (cmd.startsWith("CXON")) 
          {
            Hardware::CX = true;
          }
          else 
          {
            Hardware::CX = false;
          }
        }

        // CMD,<TEAM_ID>,ST,<UTC_TIME>|GPS
        else if (enableST && cmd.startsWith("ST")) 
        {
          if (cmd.startsWith("STGPS"))
          {
            // Set to GPS time
            setTime(Hardware::gps_data.hours, Hardware::gps_data.minutes, Hardware::gps_data.seconds, day(), month(), year());
          }
          else 
          {
            // Set to utc time
            String utc = cmd.substring(2,cmd.length());

            int hour = utc.substring(0, 2).toInt();
            int minute = utc.substring(3, 5).toInt();
            int seconds = utc.substring(6, 8).toInt();

            setTime(hour, minute, seconds, day(), month(), year());
          }
        }

        // CMD,<TEAM_ID>,SIM,<MODE>
        else if (enableSIM && cmd.startsWith("SIM")) 
        {
          if (cmd.startsWith("SIMENABLE")) 
          {
            Hardware::SIM_ENABLE = true;
          }
          else if (cmd.startsWith("SIMACTIVATE")) 
          {
            if (Hardware::SIM_ENABLE) 
            {
              Hardware::SIM_ACTIVATE = true;
            }
          }
          else if (cmd.startsWith("SIMDISABLE")) 
          {
            Hardware::SIM_ENABLE = false;
            Hardware::SIM_ACTIVATE = false;
          }
        }

        // CMD,<TEAM_ID>,SIMP,<PRESSURE>
        else if (enableSIM && cmd.startsWith("SIMP")) 
        {
          Hardware::SIM_PRESSURE = cmd.substring(4,cmd.length()).toInt();
        }

        // CMD,<TEAM_ID>,CAL 
        else if (enableCAL && cmd.startsWith("CAL")) 
        {
          Hardware::read_sensors();
          Hardware::EE_BASE_PRESSURE = Hardware::sensor_data.pressure / 100;
          // TODO: EEPROM.put(Common::BP_ADDR, Hardware::EE_BASE_PRESSURE);
        }

        // CMD,<TEAM_ID>,BCN,ON|OFF
        else if (enableMEC && cmd.startsWith("MEC"))
        {
          if (cmd.startsWith("MECBZON")) 
          {
            Hardware::buzzer_on();
          }
          else if(cmd.startsWith("MECLLOPEN"))
          {
            Hardware::leg1.write(180);
            Hardware::leg2.write(180);
            Hardware::leg3.write(180);
          }
        }
      
      }
    }
  }

  String build_packet(String state)
  {
    // <TEAM_ID>, <MISSION_TIME>, <PACKET_COUNT>, <MODE>, <STATE>, <ALTITUDE>,
    // <AIR_SPEED>, <HS_DEPLOYED>, <PC_DEPLOYED>, <TEMPERATURE>, <VOLTAGE>,
    // <PRESSURE>, <GPS_TIME>, <GPS_ALTITUDE>, <GPS_LATITUDE>, <GPS_LONGITUDE>,
    // <GPS_SATS>, <TILT_X>, <TILT_Y>, <ROT_Z>, <CMD_ECHO>
    String packet = String(Common::TEAM_ID) + ",";
    packet += String(hour()) + ":" + String(minute()) + ":" + String(second()) + ",";
    packet += String(Hardware::EE_PACKET_COUNT) + ",";
    if (Hardware::SIM_ACTIVATE && Hardware::SIM_ENABLE)
      packet += "S,";
    else
      packet += "F,";
    packet += state + ",";
    packet += String(Hardware::sensor_data.altitude) + ","; 
    packet += String(Hardware::sensor_data.temperature) + ",";
    packet += String(Hardware::sensor_data.pressure) + ",";
    packet += String(Hardware::sensor_data.vbat) + ",";
    packet += String(Hardware::sensor_data.gyro_r) + ",";
    packet += String(Hardware::sensor_data.gyro_p) + ",";    
    packet += String(Hardware::sensor_data.gyro_y) + ",";
    packet += String(Hardware::sensor_data.accel_r) + ",";
    packet += String(Hardware::sensor_data.accel_p) + ",";    
    packet += String(Hardware::sensor_data.accel_y) + ",";
    packet += String(Hardware::sensor_data.mag_r) + ",";
    packet += String(Hardware::sensor_data.mag_p) + ",";    
    packet += String(Hardware::sensor_data.mag_y) + ",";
    packet += String(Hardware::sensor_data.auto_gyro_speed) + ",";
    packet += String(Hardware::gps_data.hours) + ":" + String(Hardware::gps_data.minutes) + ":" + String(Hardware::gps_data.seconds) + ",";
    packet += String(Hardware::gps_data.altitude) + ",";  
    packet += String(Hardware::gps_data.latitude) + ","; 
    packet += String(Hardware::gps_data.longitude) + ","; 
    packet += String(Hardware::gps_data.sats) + ",";
    packet += Hardware::lastCMD + "\r\n";

    ++Hardware::EE_PACKET_COUNT;
    // TODO: EEPROM.put(Common::PC_ADDR, Hardware::EE_PACKET_COUNT);

    return packet;
  }


}