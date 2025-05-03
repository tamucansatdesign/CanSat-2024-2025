#include <Adafruit_GPS.h>

// Initialize the GPS using hardware serial (adjust if needed)
Adafruit_GPS gps(&Serial8);

// Define a struct to hold GPS data
struct {
  int hours;
  int minutes;
  int seconds;
  int milliseconds;
  float latitude;
  float longitude;
  float altitude;
  byte sats;
} gps_data;

void setup() {
  Serial.begin(115200);  // USB Serial for debugging
  while (!Serial);       // Wait for Serial Monitor to open

  setup_GPS();
}

void loop() {
  read_gps();

  // Print all GPS data in one block
  Serial.print("Time: ");
  Serial.print(gps_data.hours);
  Serial.print(":");
  Serial.print(gps_data.minutes);
  Serial.print(":");
  Serial.print(gps_data.seconds);
  Serial.print(".");
  Serial.println(gps_data.milliseconds);

  Serial.print("Latitude: ");
  Serial.println(gps_data.latitude, 8);
  Serial.print("Longitude: ");
  Serial.println(gps_data.longitude, 8);
  Serial.print("Altitude: ");
  Serial.println(gps_data.altitude);
  Serial.print("Satellites: ");
  Serial.println(gps_data.sats);

  Serial.println("--------------------------");

  delay(1000);  // Wait 1 second between readings
}

// Initialize GPS (same as before)
void setup_GPS() {
  Serial.println("\nInitializing GPS...");

  gps.begin(9600); // Start GPS at 9600 baud

  if (!gps.begin(9600)) {
    Serial.println("Could not find GPS, check wiring! womp womp :(");
    while (1) { delay(10); }
  }
  else {
    Serial.println("Found GPS successfully.");
  }
  delay(1000);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
}

// Read GPS data (same as before)
void read_gps() {
  bool newData = false;

  while (!gps.newNMEAreceived()) {
    char c = gps.read();
  }
  newData = gps.parse(gps.lastNMEA());

  if (newData) {
    // Optional: setTime(gps.hour, gps.minute, gps.seconds, gps.day, gps.month, gps.year);
  }

  gps_data.hours = gps.hour;
  gps_data.minutes = gps.minute;
  gps_data.seconds = gps.seconds;
  gps_data.milliseconds = gps.milliseconds;
  gps_data.latitude = gps.latitude;
  gps_data.longitude = gps.longitude;
  gps_data.altitude = gps.altitude;
  gps_data.sats = (byte)(unsigned int)gps.satellites;
}
