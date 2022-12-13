#ifndef WHITELIGHT_H
#define WHITELIGHT_H
#include <Arduino.h>

// WHITE LIGHT SCHEDULE
// ALARM #1
extern bool enableWhiteLightAlarm_A1;
#define WHITE_LIGHT_ON_HOUR_A1 6         // start of the on window of this device: HOUR
#define WHITE_LIGHT_OFF_HOUR_A1 9         // end of the on window of this device: HOUR
#define WHITE_LIGHT_ON_INTERVAL_A1 30000 // the amount of time this device stays powered on for: input in minutes
#define WHITE_LIGHT_OFF_INTERVAL_A1 30000 // the amount of time this device stays powered off for: input in minutes

// ALARM #2
extern bool enableWhiteLightAlarm_A2;
#define WHITE_LIGHT_ON_HOUR_A2 10         // start of the on window of this device: HOUR
#define WHITE_LIGHT_OFF_HOUR_A2 1         // end of the on window of this device: HOUR
#define WHITE_LIGHT_ON_INTERVAL_A2 30000 // the amount of time this device stays powered on for: input in minutes
#define WHITE_LIGHT_OFF_INTERVAL_A2 30000 // the amount of time this device stays powered off for: input in minutes

// ALARM #3
extern bool enableWhiteLightAlarm_A3;
#define WHITE_LIGHT_ON_HOUR_A3 14         // start of the on window of this device: HOUR
#define WHITE_LIGHT_OFF_HOUR_A3 17         // end of the on window of this device: HOUR
#define WHITE_LIGHT_ON_INTERVAL_A3 30000 // the amount of time this device stays powered on for: input in minutes
#define WHITE_LIGHT_OFF_INTERVAL_A3 30000 // the amount of time this device stays powered off for: input in minutes

// WHITE LIGHT SETTINGS
#define WHITE_LIGHT_PIN 4           // gpio pin relay is connected to
extern bool whiteLightCurrentState;     // state of the relay when it is currently time to be on
extern bool isWhiteLightRunning; // is it currently time for the relay to be on
extern bool isWhiteLightFirstCycle;    // is this the first time relay is on during this time slot
extern int whiteLightTotalAmountOfCycles;
extern int whiteLightCurrentAmountOfCycles;

// WHITE LIGHT FUNCTIONS
void setupWhiteLight();
void printWhiteLightStatus();
void turnWhiteLightOn();
void turnWhiteLightOff();


#endif