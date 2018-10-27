
// ******************** ******************** ******************** //
// Low-Power Functions                                            //
// ******************** ******************** ******************** //

/* ---------------------------------------------
 * Deep Sleep for n minutes
 * ---------------------------------------------  */

// Deep sleep for n minutes //
void waitMinutes(int minutes)
{
  for(int i=0;i<minutes;i++)
  {
    waitOne();
  }
}


/* ---------------------------------------------
 * Deep Sleep for 1 minutes
 * ---------------------------------------------  */
 
// One minute low power //
void waitOne(void)
{
  for(int i = 0;i<6;i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  }
}



/* ---------------------------------------------
 * Software based reboot (Watchdog)
 * ---------------------------------------------  */

void softReboot()
{
  wdt_enable(WDTO_15MS);
  while(1){}
}




