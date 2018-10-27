
// ******************** ******************** ******************** //
//   Data Processing                                              //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to update sensor data
 * ---------------------------------------------  */
int checkSensors(void)
{
  digitalWrite(SENSOR_POWER, HIGH);
  delay(100);
  Serial.println(">Check Voltage: ");
  checkVoltage();
  Serial.println(">Check Water Level: ");
  checkWater();
  Serial.println(">Check Light Level: ");
  checkLight();
  Serial.println(">Check Battery Temp: ");
  checkBatteryTemp();
  digitalWrite(SENSOR_POWER, LOW);
}



/* ---------------------------------------------
 * Function to update water level sensor data
 * ---------------------------------------------  */
int checkWater(void)
{
  //Serial.println("Check Water");
  variable.waterLow = readWaterLow();
  variable.waterEmpty = readWaterEmpty();
}


/* ---------------------------------------------
 * Function to update light level sensor data
 * ---------------------------------------------  */
int checkLight(void)
{
  //Serial.println("Check Light");
  variable.light = map(readLight(), 0, 1024, 100, 0);
}


/* ---------------------------------------------
 * Function to update Voltage Level sensor data
 * ---------------------------------------------  */
int checkVoltage(void)
{

  Serial.print("Check Vcc: ");
  defaults.Vcc = checkVcc();
  Serial.println(defaults.Vcc);
  
  Serial.println("Check Voltage");
  int voltageInt = map(readVoltage(), 0, 1024, 0, defaults.max_voltage_read*100);
  Serial.print("Voltage: ");
  
  variable.voltage = (float)voltageInt / 100;
  Serial.println(variable.voltage);
  return (int)variable.voltage;
}

