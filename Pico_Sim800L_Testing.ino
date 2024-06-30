//Serial2 Rx to PI PICO Pin8
//Serial2 Tx to PI PICO Pin9

void setup() {
  delay(10000);
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial2.println("AT");  // AT Command test
  updateSerial();
  Serial2.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  delay(500);
}

void loop() {
  updateSerial();
}


void updateSerial()
{
  while (Serial.available()) 
  {
    char c = Serial.read();
    Serial2.write(c);  // Forward character to Software Serial Port

    // Check for incoming message
    static String messageBuffer;
    messageBuffer += c;

    if (c == '\n') // Assuming the end of a message is marked by a newline character
    {
      if (messageBuffer.indexOf("+CMTI:") != -1)
      {
        // Handle the incoming message here
        Serial.println("Received a message: " + messageBuffer);
        // Add your logic to process the message
      }

      messageBuffer = ""; // Clear the message buffer
    }
  }

  while (Serial2.available()) 
  {
    char c = Serial2.read();
    Serial.write(c);  // Forward character to Serial Port
  }
}

