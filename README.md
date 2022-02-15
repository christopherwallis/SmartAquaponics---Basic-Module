# SmartAquaponics
Low level module used to control aquaponics system. 
- Controls system behaviour (pump time etc) based on sensor data (battery, moisture, light) and data collected from external sources. 
- Designed to run autonomously if sensors fail or conectivity is lost to higher level modules / server. 
- Sensor data and system behavior is passed to higher level modules and recorded on server for analytics.

Coded using Arduino language, designed for use on ATMega128 with custom PCB and sensors. System to communicate with ESP32 via serial (requires level conversion) for external conectivity and data logging.
