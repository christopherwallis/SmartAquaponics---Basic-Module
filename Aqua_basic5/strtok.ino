//***Basic Data***//
void strtokTiming(void)
{
  //String input;
  Serial.print("Input string: ");
  Serial.println(timingdata);
  int basic[3];
  byte i = 0;
  // Remove send reply
  char current = timingdata[i];
  while(current != '&')
  {
    Serial.print(current);
    i++;
    current = timingdata[i];
  }
  Serial.println(" ");
  Serial.print("Input trimmed: ");
    
  //Serial.println(timingdata);
  i++;
  byte j = 0;
  // Collect data terms
  current = timingdata[i];
  char data[8];
  for(byte k = 0; k < 2; k++){
    Serial.print(k);
    Serial.print(": ");
    while (current != '&') 
    {
        data[j] = current;
        j++;
        i++;
        Serial.print(current);
        current = timingdata[i];
    }
    data[j]='\0';  
    i++;
    current = timingdata[i];
    basic[k] = atoi(data);
    j = 0;
    Serial.println(" ");
  }
  Serial.println(" ");
  Serial.println("Data:");
  // Print variables
  for (int i = 0; i<2; i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(basic[i]);
  }
  
  // Store timing
  variable.timeOn = (byte)basic[0];
  Serial.print("TimeOn: ");
  Serial.println(variable.timeOn);
  variable.timeOn = constrain(variable.timeOn, 0, 45);
  variable.timeOff = (byte)basic[1];  
  Serial.print("TimeOff: ");
  Serial.println(variable.timeOff);
  variable.timeOff = constrain(variable.timeOff, 0, 60);

}
