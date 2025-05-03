import serial

# Set your USB XBee's COM port and baud rate
XBEE_PORT = 'COM5'    # Change to your actual COM port, e.g., 'COM3' or '/dev/ttyUSB0'
BAUD_RATE = 115200

def main():
    with serial.Serial(XBEE_PORT, BAUD_RATE, timeout=1) as ser:
        print(f"Listening on {XBEE_PORT} at {BAUD_RATE} baud...")
        
        while True:
            line = ser.readline().decode('utf-8', errors='replace').strip()
            if line:
                print(f"Received: {line}")

if __name__ == "__main__":
    main()
