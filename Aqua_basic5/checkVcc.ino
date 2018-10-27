long checkVcc() {

  // Internal voltage read and scaled Vcc from TheDITGuy999 on GitHub (and many other sources)
  // Edited to for the project and additional functionality
  // Read 1.1V reference against AVcc (ie Vint / Vcc)
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  
  // Now use Vint and it's known value to detemine accurate Vcc
  long result = (high<<8) | low;
  Serial.print("Internal '1.1V' Voltage: ");
  Serial.println(defaults.internal_voltage);
  long expected = long(defaults.internal_voltage * 1023 * 1000);
  Serial.print("Internal voltage as long: ");
  Serial.println(expected);
  result = expected / result; // Where expected is the Voltage of Vint in millivolts * 1023 and result is [1023 * Vint / Vcc] => = Vcc in millivolts
  Serial.print("Results: ");
  Serial.println(result);
  // Convert Vcc to volts (float) and store,
  defaults.Vcc = float(result) / 1000;
  
  // Calculate max voltage read and store
  defaults.max_voltage_read = defaults.Vcc * defaults.ratio;
  Serial.print("Ratio: ");
  Serial.println(defaults.ratio);
  Serial.print("Max V Read: ");
  Serial.println(defaults.max_voltage_read);
  
  return result;
}
