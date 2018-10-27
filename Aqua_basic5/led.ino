
// ******************** ******************** ******************** //
//   LED Display                                                  //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Function to Set LED Outputs 
 * INPUTS: Communications, Water, Battery
 * 0: No change
 * 1: OFF
 * 2: Flash
 * 3: ON
 * ---------------------------------------------  */

void setLED(byte orange, byte red)
{
  // Red LED
  switch (red) {
    case 0:
      // No change
      break;
    case 1:
      // Red OFF
      digitalWrite(LED_RED, LOW);
      break;
    case 2:
      // Red Flash
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(LED_RED, HIGH);
        delay(250);
        digitalWrite(LED_RED, LOW);
        delay(250);
      }
      break;
    case 3:
      // Red ON
      digitalWrite(LED_RED, HIGH);
      break;
  }
  
  // Orange LED
  switch (orange) {
    case 0:
      // No change
      break;
    case 1:
      // Orange OFF
      digitalWrite(LED_ORANGE, LOW);
      break;
    case 2:
      // Orange Flash
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(LED_ORANGE, HIGH);
        delay(250);
        digitalWrite(LED_ORANGE, LOW);
        delay(250);
      }
      break;
    case 3:
      // Orange ON
      digitalWrite(LED_ORANGE, HIGH);
      break;
  }
}

