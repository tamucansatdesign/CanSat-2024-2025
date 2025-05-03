// Teensy 4.1 XBee simple transmitter

#define GROUND_XBEE_SERIAL Serial8  // XBee connected to Serial1 (pins 0 and 1)

void setup() {
  Serial.begin(115200);              // USB Serial monitor
  while (!Serial);                 // Wait for USB Serial
  GROUND_XBEE_SERIAL.begin(115200);  // Start XBee serial
  Serial.println("XBee transmitter started");
}

void loop() {
  // Example: Send a consistent message every second
  String message = "Hello from Teensy!";
  write_ground_radio(message);

  Serial.print("Sent: ");
  Serial.println(message);

  delay(1000);  // Wait 1 second between messages
}

// Sends a string to the XBee radio
void write_ground_radio(const String &data) {
  GROUND_XBEE_SERIAL.println(data);
}
