/*
  Smart Home Solution
  Aquaponics system
  Basic Automation - Arduino Nano
*/


// ******************** //
//   Initial Setup      //
// ******************** //


// Pump on/off polarity
#define PUMPON LOW
#define PUMPOFF HIGH
#define TESTVOLTAGE 0
#define TESTWATER 1
#define TESTMODE 1

// Included libraries
#include <OneWire.h>
#include <avr/wdt.h>
#include <LowPower.h>
#include <SoftwareSerial.h>



// Pin Assignment
#define LIGHT_SENSOR A1
#define WATER_LOW 2
#define WATER_EMPTY 3
#define VOLTAGE_SENSOR A0
#define BATT_TEMP_PIN 9
#define BATT_TEMP_POWER 10
#define PUMP_RELAY_PIN 7
#define LED_RED 4
#define LED_ORANGE 5
#define SENSOR_POWER 8
#define DEFAULT_TIMEON 3
#define DEFAULT_TIMEOFF 60

// Serial to Smart
#define MYSERIAL_RX 11 // Blue
#define MYSERIAL_TX 12 // Blue and white

// System Values
// #define MAX_VOLTAGE_READ 25


// Data Structures
struct basicDefaults
{
  // Voltage
  float max_voltage_read;
  float internal_voltage;
  float Vcc;
  float ratio;
  byte tempAddr[8];
  float voltage_low;
  float voltage_empty;
};

struct basicVariable
{
  // Sensor Data
  byte waterLow;
  byte waterEmpty;
  byte light;
  float voltage;
  float celsius;
  byte fillTime;
  
  // Timing
  int timeOn;
  int timeOff;
};

char timingdata[64];
// Global variables

basicDefaults defaults = 
{
  // Max battery read voltage
  30.0,
  // Internal 1.1 voltage, actual read
  1.1037,
  // Vcc default and voltage divider ratio default
  5.00, 6.096,
  // Temp probe address
  {0x28, 0xFF, 0xD0, 0x17, 0x69, 0x14, 0x04, 0x35},
  // Voltage low / empty
  12.2, 12.0
};

basicVariable variable = 
{
  // Sensors
  1, 1, 0, 12.5, 25.0, 0,
  // Timing 
  DEFAULT_TIMEON, DEFAULT_TIMEOFF
};


// Battery temp probe object
OneWire ds(BATT_TEMP_PIN);

// Serial Connection to Smart Module
SoftwareSerial mySerial(MYSERIAL_RX, MYSERIAL_TX);

// ******************** ******************** ******************** ******************** //
//   Main Functions                                                                    //
// ******************** ******************** ******************** ******************** //


/* ---------------------------------------------
 * Initialisation setup function
 * ---------------------------------------------  */
void setup() 
{
  
  // Debugging USB serial
  Serial.begin(9600);
  Serial.println(">>>RESTART<<<");
  // Set up output pins
  pinMode(BATT_TEMP_POWER, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  digitalWrite(PUMP_RELAY_PIN, PUMPOFF);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(SENSOR_POWER, OUTPUT);
}


/* ---------------------------------------------
 * Looped function - continuous run
 * ---------------------------------------------  */
void loop() 
{
  Serial.println("**************************************");
  Serial.println("***       Smart Aquaponics         ***");
  Serial.println("***         Basic Module           ***");
  Serial.println("***            V4.0                ***");
  Serial.println("***          2018-06-21            ***");
  Serial.println("***      Christopher Wallis        ***");
  Serial.println("**************************************");
  Serial.println(" ");
  // Confirm pump off
  Serial.println("###Pump Turned Off###");
  controlPump(PUMPOFF);
  resetTiming();
  delay(100);

  
  // Get Sensor Data
  Serial.println(">>>Check Sensors");
  checkSensors();
  //Serial.println(">>>Sensordata collected");

  Serial.println(" ");
  // Print data to usb for debugging
  sendSensorData();

  if (variable.waterLow == 0) {
    setLED(0, 2);
  }
  delay(1000);
  // Send data to smart controller and Get smart control timing
  if (TESTMODE == 0) {
    Serial.println(" ");
    Serial.println(">>>Get smart timing");
    int check = getSmartTiming();
    Serial.print("Error check: ");
    Serial.println(check);
    if (check == 1) {
      Serial.println(">>>Saving smart timing data: ");
      strtokTiming();
      delay(1000);
      mySerial.println('C');
      delay(100);
      mySerial.println('C');
    }
  
  // Set communication light if smart timing controlled
    setLED(check, 0);
  }
  // If water level check enabled, ensure water level is OK
  if (TESTWATER)
  {
    if (variable.waterEmpty == 0) {
     variable.timeOn = 0;
     setLED(0, 3); 
    }
  }
  
  // On period
  Serial.println("On Period");
  onPeriod();
 
  setLED(1, 1);
  // Off period
  Serial.println("Off Period");
  offPeriod();

}




