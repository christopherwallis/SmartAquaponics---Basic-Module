// ******************** ******************** ******************** //
//   Cycles                                                       //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to control the pump in the "On Mode"
 * -------------------------------------------- */
 
byte onPeriod(void)
{
  // Variables for in loop checking
  float voltageCheck = variable.voltage;

  // Turn LEDs off
  setLED(1, 1);

  Serial.print("timeOn = ");
  Serial.println(variable.timeOn);
  
  // If Voltage check enabled, ensure voltage level OK
  if (TESTVOLTAGE)
    {
      if(testVoltageOn() == 0)
      {
        return 1;
      }
    }
  if (TESTWATER)
    {
      if(testWaterOn() != 0)
      {
        return 2;
      }
    }
  delay(1000);
  Serial.print("timeON: ");
  Serial.println(variable.timeOn);
  if (variable.timeOn > 0)
  {
    controlPump(PUMPON);
    
    Serial.println("###Pump Turned ON###");
    // fill check
    // variable.timeOn--;
  }
  delay(50);
  

  // Finish on period while checking voltage  
  while (variable.timeOn > 0)
  {
    variable.timeOn--;
    delay(100);
    waitOne();
    
    delay(100);
    // If Voltage check enabled, ensure voltage level OK
    if (TESTVOLTAGE)
    {
      if(testVoltageOn() == 0)
      {
        return 1;
      }
    }
    if (TESTWATER)
    {
      if(testWaterOn() != 0)
      {
        return 2;
      }
    }
    // Time Left
    Serial.println(variable.timeOn);
  }
  return 0;
}


int testVoltageOn(void)
{
    float voltageCheck = checkVoltage();
    
    if (voltageCheck > defaults.voltage_empty)
    {
      setLED(3, 0);
      delay(500);
      setLED(1, 0);
    } else {
      controlPump(PUMPOFF);
      
      Serial.println("###Pump Turned Off###");
      setLED(0, 3);
      Serial.println("LOW VOLTAGE FAIL");
      return 1;
    }
    
}

int testWaterOn(void)
{
    
    if (readWaterEmpty() == 0)
    {
      controlPump(PUMPOFF);
      Serial.println("###Pump Turned Off###");
      setLED(0, 3);
      Serial.println("LOW WATER FAIL");
      return 1;
    } else {
      if (readWaterLow() == 0)
      {
        setLED(0, 3);
        delay(500);
        setLED(0, 1);
      }
    }
    return 0;
}
/* ---------------------------------------------
 * Function to control the pump in the "Off Mode"
 * -------------------------------------------- */

void offPeriod(void)
{
  Serial.print("timeOff = ");
  Serial.println(variable.timeOff);
  delay(1000);

  // Turn LEDs off
  setLED(1, 1);

  // Turn Pump Off
  if (variable.timeOff > 0)
  {
    controlPump(PUMPOFF);
    Serial.println("###Pump Turned Off###");
    delay(500);
  }

  // Wait for off period to end
  Serial.println("Waiting for off cycle...");
  delay(1000);
  waitMinutes(variable.timeOff);
  Serial.println("Wait over");
}
