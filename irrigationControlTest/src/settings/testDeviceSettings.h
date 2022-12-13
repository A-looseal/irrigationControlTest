#ifndef TESTDEVICESETTINGS_H
#define TESTDEVICESETTINGS_H
#include <Arduino.h>

// TEST DEVICE SCHEDULE
// ALARM #1  (5AM - 6AM)
extern bool enableTestDeviceAlarm_A1;
#define TEST_DEVICE_ON_HOUR_A1 9         // start of the on window of this device: HOUR
#define TEST_DEVICE_ON_MINUTE_A1 0         // start of the on window of this device: HOUR
#define TEST_DEVICE_OFF_HOUR_A1 10         // end of the on window of this device: HOUR
#define TEST_DEVICE_OFF_MINUTE_A1 9         // end of the on window of this device: HOUR
#define TEST_DEVICE_ON_INTERVAL_A1 2 // the amount of time this device stays powered on for: input in minutes
#define TEST_DEVICE_OFF_INTERVAL_A1 1 // the amount of time this device stays powered off for: input in minutes

// ALARM #2  (9AM - 10AM)
extern bool enableTestDeviceAlarm_A2;
#define TEST_DEVICE_ON_HOUR_A2 11         // start of the on window of this device: HOUR
#define TEST_DEVICE_OFF_HOUR_A2 12         // end of the on window of this device: HOUR
#define TEST_DEVICE_ON_INTERVAL_A2 2 // the amount of time this device stays powered on for: input in minutes
#define TEST_DEVICE_OFF_INTERVAL_A2 1 // the amount of time this device stays powered off for: input in minutes

// ALARM #3 (1PM - 2PM)
extern bool enableTestDeviceAlarm_A3;
#define TEST_DEVICE_ON_HOUR_A3 13         // start of the on window of this device: HOUR
#define TEST_DEVICE_OFF_HOUR_A3 14         // end of the on window of this device: HOUR
#define TEST_DEVICE_ON_INTERVAL_A3 4 // the amount of time this device stays powered on for: input in minutes
#define TEST_DEVICE_OFF_INTERVAL_A3 1 // the amount of time this device stays powered off for: input in minutes

// ALARM #4 (6PM - 7PM)
extern bool enableTestDeviceAlarm_A4;
#define PUMP_ON_HOUR_A4 18         // start of the on window of this device: HOUR
#define PUMP_OFF_HOUR_A4 19         // end of the on window of this device: HOUR
#define PUMP_ON_INTERVAL_A4 5 // the amount of time this device stays powered on for: input in minutes
#define PUMP_OFF_INTERVAL_A4 10 // the amount of time this device stays powered off for: input in minutes

// TEST DEVICE SETTINGS
#define TEST_DEVICE_PIN 13           // gpio pin relay is connected to
extern bool testDeviceCurrentState;     // state of the relay when it is currently time to be on
extern bool isTestDeviceRunning; // is it currently time for the relay to be on
extern bool isTestDeviceFirstCycle;    // is this the first time relay is on during this time slot
extern int testDeviceTotalAmountOfCycles;
extern int testDeviceCurrentAmountOfCycles;

// TEST DEVICE FUNCTIONS
void setupTestDevice();
void printTestDeviceStatus();
void turnTestDeviceOn();
void turnTestDeviceOff();


#endif