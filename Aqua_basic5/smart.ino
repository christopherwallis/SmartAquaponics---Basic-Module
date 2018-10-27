// ******************** ******************** ******************** //
//   SMART CONTROL                                                //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to set the timing to default
 * -------------------------------------------- */
void resetTiming(void)
{
  variable.timeOn = DEFAULT_TIMEON;
  variable.timeOff = DEFAULT_TIMEOFF;
}


byte getSmartTiming(void)
{
  wdt_disable();
  Serial.println(">>>Opening Serial Connection");
  // Wait for serial data
  mySerial.begin(9600);
  unsigned long timeout = millis();
  Serial.println(">>>Wait for signal");
  byte count = 0;
  mySerial.print("D");
  while (!mySerial.available()) {
    if (millis() - timeout > 100000) {
      Serial.println(">>> Smart Serial Timeout (D1)! <<<");
      return 2;
    }
    count++;
    delay(1);
    if (count > 1000) {
      Serial.print(".");
      count = 0;
    }
  }
  // Wait for response
  Serial.println(">>>Serial Connection established");
  // Wait for request
  timeout = millis();
  char incoming = (char)mySerial.read();
  Serial.print("Incoming: ");
  Serial.print(incoming);
  count = 0;
  while (incoming != 'D')
  {
    incoming = (char)mySerial.read();
    Serial.print(incoming);
    if (millis() - timeout > 10000)
    {
      Serial.println("Request from Smart not received (D2)");
      return 2;
    }
    count++;
    delay(1);
    if (count > 1000) {
      Serial.print(".");
      count = 0;
    }
  }
  //mySerial.flush();
  delay(500);
  Serial.println();
  Serial.println(">>>Sending sensor data to Smart:");
  // Send requested data
  mySerial.print("data");
  mySerial.print("&");
  mySerial.print(variable.waterLow);
  mySerial.print("&");
  mySerial.print(variable.waterEmpty);
  mySerial.print("&");
  mySerial.print(variable.light);
  mySerial.print("&");
  mySerial.print(variable.voltage);
  mySerial.print("&");
  mySerial.print(variable.celsius);
  mySerial.println("&");
  Serial.print("data");
  Serial.print("&");
  Serial.print(variable.waterLow);
  Serial.print("&");
  Serial.print(variable.waterEmpty);
  Serial.print("&");
  Serial.print(variable.light);
  Serial.print("&");
  Serial.print(variable.voltage);
  Serial.print("&");
  Serial.print(variable.celsius);
  Serial.println("&");

  Serial.println(">>>Wait for timing calculations.");

  mySerial.begin(9600);
  timeout = millis();
  
  // Wait for connection
  count = 0;
  while (mySerial.available() == 0) {
    count++;
    delay(1);
    if (count > 1000) {
      Serial.print(".");
      count = 0;
    }
    if (millis() - timeout > 200000) {
      Serial.println(">>> Smart Serial Timeout (T1)!");
      delay(1000);
      return 2;
    }
  }
  char waitForTiming = ' ';
  Serial.println(">>>Connection OK");
  int error = 0;
  // Wait for T char
  timeout = millis();
  while (waitForTiming != 'T')
  {
    waitForTiming = (char)mySerial.read();
    count++;
    delay(1);
    if (count > 1000) {
      Serial.print(".");
      count = 0;
    }
    if (millis() - timeout > 100000) {
      Serial.println(">>> Smart Serial Timeout Step 1 (T2)!");
      error = 1;
      break;
    }
  }
  // Second waiting period
  if (error == 1)
  {
    timeout = millis();
    Serial.println(">>> Second attempt to get data:");
    while (waitForTiming != 'T')
    {
      waitForTiming = (char)mySerial.read();
      if (millis() - timeout > 100000) {
        Serial.println(">>> Smart Serial Timeout Step 2 (T2)!");
        return 2;
      }
    }
  }
  Serial.println(">>>Confirmation received.. sending reply.");
  delay(100);
  // Reply with confirmation
  mySerial.print("T");
  delay(500);
  // Wait for data on serial connection
  timeout = millis();
  while (mySerial.available() == 0)
  {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Smart Serial Timeout (T3)!");
      delay(1000);
      return 2;
    }
  }
  byte i = 0;
  //char incoming;
  // Get received message
  while(mySerial.available()){
    
    incoming = (char)mySerial.read();
    timingdata[i] = incoming;
    Serial.print(incoming);
    i++;
    // end on end of line
    if (incoming == '\n') {
      Serial.print("Input string from smart: ");
      Serial.println(timingdata);
      return 1;
    }
  }
  Serial.println("Fail to find end of string...");
  // return 1=OK, 2=warning, 0=error/no control
  return 2;
}
