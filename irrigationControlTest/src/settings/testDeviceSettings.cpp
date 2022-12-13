#include "testDeviceSettings.h"

#define ENABLE_SERIAL_OUTPUT

#pragma region VARIABLES
// PUMP SETTINGS
#define TEST_DEVICE_PIN 13           // gpio pin relay is connected to
bool testDeviceCurrentState = false;     // state of the relay when it is currently time to be on
bool isTestDeviceRunning = false; // is it currently time for the relay to be on
bool isTestDeviceFirstCycle = true;    // is this the first time relay is on during this time slot
int testDeviceTotalAmountOfCycles;
int testDeviceCurrentAmountOfCycles;

// PUMP ALARM SETTINGS
bool enableTestDeviceAlarm_A1 = true;
bool enableTestDeviceAlarm_A2 = false;
bool enableTestDeviceAlarm_A3 = false;
#pragma endregion

/*
SETUP PUMP
initializes the pump and performs all setup housekeeping
*/
void setupTestDevice()
{
    pinMode(TEST_DEVICE_PIN, OUTPUT);                // initializes the GPIO as an OUTPUT
    digitalWrite(TEST_DEVICE_PIN, HIGH); // turns the pump off
#ifdef ENABLE_SERIAL_OUTPUT                   // only output to the serial console if enabled
    Serial.println("test Device Setup Complete."); // print status of the setup sequence to serial console
#endif
    // TODO: print setup status to the OLED display
    delay(500); // delay for a tiny bit during the startup process
}

/*
PRINT PUMP STATUS
prints the current status of the pump
*/
void printTestDeviceStatus()
{
#ifdef ENABLE_SERIAL_OUTPUT       // only output to the serial console if enabled
    Serial.print("Test Device State: "); // print the current state of this realy to the serial console
    Serial.println(testDeviceCurrentState);

    Serial.print("Test Device Total Cycles: "); // prints the total amount of times this relay has cycled
    Serial.println(testDeviceTotalAmountOfCycles);
#endif
    // TODO: print test Device state on the oled display
    // TODO: print test Device total cycles on the oled display
}

/*
TURN PUMP ON
turns the pump on
*/
void turnTestDeviceOn()
{
    digitalWrite(TEST_DEVICE_PIN, HIGH); // turns the pump on
    testDeviceCurrentState = true;      // set the flag that tracks state to true
}

/*
TURN PUMP OFF
turns the pump off
*/
void turnTestDeviceOff()
{
    digitalWrite(TEST_DEVICE_PIN, LOW); // turns the pump off
    testDeviceCurrentState = false;    // set the flag that tracks state to false
}

