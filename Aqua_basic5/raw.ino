
// ******************** ******************** ******************** //
// Raw Data Acquisition                                           //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to read battery temperature
 * ---------------------------------------------  */
int checkBatteryTemp(void)
{
  
  
  // Necessary Variables
  byte data[12];
  byte i;
  byte present = 0;
  byte type_s = 0;
  
  // Get data from probe
  Serial.println("Check Battery Temp");
  // Power to probe
  digitalWrite(BATT_TEMP_POWER, HIGH);
  // Delay for stability
  delay(20);        
  ds.reset();
  ds.select(defaults.tempAddr);
  ds.write(0x44, 1);
  
  // Wait for response 
  delay(1000);     // maybe 750ms is enough, maybe not
  
  // Read data
  present = ds.reset();
  ds.select(defaults.tempAddr);    
  ds.write(0xBE);
  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to celcius temperature
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }

  // Store in struct
  variable.celsius = (float)raw / 16.0;
  
  // Debugging data to serial 
  Serial.print("Battery Temp: ");
  Serial.println(variable.celsius);
  
  // Turn off power to probe
  digitalWrite(BATT_TEMP_POWER, LOW);
}



/* ---------------------------------------------
 * Function to return low water sensor state
 * ---------------------------------------------  */
int readWaterLow(void)
{
  Serial.println("Read Water Low");
  digitalWrite(SENSOR_POWER, HIGH);
  // 1ms Delay for stability
  delay(1);        
  int digitalValue = digitalRead(WATER_LOW);
  digitalWrite(SENSOR_POWER, LOW);
  return(digitalValue);
}


/* ---------------------------------------------
 * Function to return empty water sensor state
 * ---------------------------------------------  */
int readWaterEmpty(void)
{
  Serial.println("Read Water Empty");
  digitalWrite(SENSOR_POWER, HIGH);
  // 1ms Delay for stability
  delay(1); 
  int digitalValue = digitalRead(WATER_EMPTY);
  digitalWrite(SENSOR_POWER, LOW);
  return(digitalValue);
}


/* ---------------------------------------------
 * Function to return light sensor analog read
 * ---------------------------------------------  */
int readLight(void)
{
  // 1ms Delay for stability
  delay(1);
  int analogValue = analogRead(LIGHT_SENSOR);
  Serial.print("Raw light: ");
  Serial.println(analogValue);
  return(analogValue);
}


/* ---------------------------------------------
 * Function to return voltage sensor analog read
 * ---------------------------------------------  */
int readVoltage(void)
{
  // 1ms Delay for stability  
  delay(1);
  int analogValue = 0;

  // Three readings
  for (int n = 0; n < 3; n++)
  {
    analogValue += analogRead(VOLTAGE_SENSOR);
    delay(20);
  }

  // Take average
  int averageVoltage = (int)analogValue/3;
  Serial.print("Raw Voltage: ");
  Serial.println(averageVoltage);
  return(averageVoltage);
}


