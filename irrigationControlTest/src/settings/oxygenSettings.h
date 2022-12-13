#ifndef OXYGENSETTINGS_H
#define OXYGENSETTINGS_H
#include <Arduino.h>

// OXYGEN SCHEDULE
// ALARM #1
extern bool enableOxygenAlarm_A1;
#define OXYGEN_ON_HOUR_A1 4         // start of the on window of this device: HOUR
#define OXYGEN_OFF_HOUR_A1 5         // end of the on window of this device: HOUR
#define OXYGEN_ON_INTERVAL_A1 30000 // the amount of time this device stays powered on for: input in minutes
#define OXYGEN_OFF_INTERVAL_A1 30000 // the amount of time this device stays powered off for: input in minutes

// ALARM #2
extern bool enableOxygenAlarm_A2;
#define OXYGEN_ON_HOUR_A2 13         // start of the on window of this device: HOUR
#define OXYGEN_OFF_HOUR_A2 14         // end of the on window of this device: HOUR
#define OXYGEN_ON_INTERVAL_A2 300000 // the amount of time this device stays powered on for: input in minutes
#define OXYGEN_OFF_INTERVAL_A2 300000 // the amount of time this device stays powered off for: input in minutes

// ALARM #3
extern bool enableOxygenAlarm_A3;
#define OXYGEN_ON_HOUR_A3 17         // start of the on window of this device: HOUR
#define OXYGEN_OFF_HOUR_A3 18         // end of the on window of this device: HOUR
#define OXYGEN_ON_INTERVAL_A3 300000 // the amount of time this device stays powered on for: input in minutes
#define OXYGEN_OFF_INTERVAL_A3 300000 // the amount of time this device stays powered off for: input in minutes

// OXYGEN SETTINGS
#define OXYGEN_PIN 3           // gpio pin relay is connected to
extern bool oxygenCurrentState;     // state of the relay when it is currently time to be on
extern bool isOxygenRunning; // is it currently time for the relay to be on
extern bool isOxygenFirstCycle;    // is this the first time relay is on during this time slot
extern int oxygenTotalAmountOfCycles;
extern int oxygenCurrentAmountOfCycles;

//OXYGEN FUNCTIONS
void setupOxygen();
void printOxygenStatus();
void turnOxygenOn();
void turnOxygenOff();


#endif