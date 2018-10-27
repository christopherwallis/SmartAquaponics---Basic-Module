
// ******************** ******************** ******************** //
//   UI                                                           //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to transmit sensor data
 * ---------------------------------------------  */
int sendSensorData(void)
{
  Serial.println("******** Sensor Data  ***************");
  Serial.print("Light level:          ");
  Serial.println(variable.light);
  Serial.print("Water low sensor:     ");
  Serial.println(variable.waterLow);
  Serial.print("Water empty sensor:   ");
  Serial.println(variable.waterEmpty);
  Serial.print("Voltage level:        ");
  Serial.println(variable.voltage);
  Serial.print("Temperature:          ");
  Serial.print(variable.celsius);
  Serial.println(" Celsius");
//  Serial.print("Fill Time: ");
//  Serial.print(variable.fillTime);
  Serial.println("*************************************");

}

