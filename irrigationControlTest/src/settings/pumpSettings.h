#ifndef PUMPSETTINGS_H
#define PUMPSETTINGS_H
#include <Arduino.h>

// PUMP SCHEDULE
// ALARM #1  (5AM - 6AM)
extern bool enablePumpAlarm_A1;
#define PUMP_ON_HOUR_A1 5         // start of the on window of this device: HOUR
#define PUMP_OFF_HOUR_A1 6         // end of the on window of this device: HOUR
#define PUMP_ON_INTERVAL_A1 30000 // the amount of time this device stays powered on for: input in minutes
#define PUMP_OFF_INTERVAL_A1 120000 // the amount of time this device stays powered off for: input in minutes

// ALARM #2  (9AM - 10AM)
extern bool enablePumpAlarm_A2;
#define PUMP_ON_HOUR_A2 9         // start of the on window of this device: HOUR
#define PUMP_OFF_HOUR_A2 10         // end of the on window of this device: HOUR
#define PUMP_ON_INTERVAL_A2 30000 // the amount of time this device stays powered on for: input in minutes
#define PUMP_OFF_INTERVAL_A2 120000 // the amount of time this device stays powered off for: input in minutes

// ALARM #3 (1PM - 2PM)
extern bool enablePumpAlarm_A3;
#define PUMP_ON_HOUR_A3 13         // start of the on window of this device: HOUR
#define PUMP_OFF_HOUR_A3 14         // end of the on window of this device: HOUR
#define PUMP_ON_INTERVAL_A3 30000 // the amount of time this device stays powered on for: input in minutes
#define PUMP_OFF_INTERVAL_A3 120000 // the amount of time this device stays powered off for: input in minutes

// ALARM #4 (6PM - 7PM)
extern bool enablePumpAlarm_A4;
#define PUMP_ON_HOUR_A4 18         // start of the on window of this device: HOUR
#define PUMP_OFF_HOUR_A4 19         // end of the on window of this device: HOUR
#define PUMP_ON_INTERVAL_A4 30000 // the amount of time this device stays powered on for: input in minutes
#define PUMP_OFF_INTERVAL_A4 120000 // the amount of time this device stays powered off for: input in minutes

// PUMP SETTINGS
#define PUMP_PIN 2           // gpio pin relay is connected to
extern bool pumpCurrentState;     // state of the relay when it is currently time to be on
extern bool isPumpRunning; // is it currently time for the relay to be on
extern bool isPumpFirstCycle;    // is this the first time relay is on during this time slot
extern int pumpTotalAmountOfCycles;
extern int pumpCurrentAmountOfCycles;

//PUMP FUNCTIONS
void setupPump();
void printPumpStatus();
void turnPumpOn();
void turnPumpOff();


#endif