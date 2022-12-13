#include "pumpSettings.h"
#define ENABLE_SERIAL_OUTPUT

#pragma region VARIABLES
// PUMP SETTINGS
#define PUMP_PIN 2           // gpio pin relay is connected to
bool pumpCurrentState = false;     // state of the relay when it is currently time to be on
bool isPumpRunning = false; // is it currently time for the relay to be on
bool isPumpFirstCycle = true;    // is this the first time relay is on during this time slot
int pumpTotalAmountOfCycles;
int pumpCurrentAmountOfCycles;

// PUMP ALARM SETTINGS
bool enablePumpAlarm_A1 = true;
bool enablePumpAlarm_A2 = false;
bool enablePumpAlarm_A3 = false;
bool enablePumpAlarm_A4 = false;
#pragma endregion

/*
SETUP PUMP
initializes the pump and performs all setup housekeeping
*/
void setupPump()
{
    pinMode(PUMP_PIN, OUTPUT);                // initializes the GPIO as an OUTPUT
    digitalWrite(PUMP_PIN, HIGH); // turns the pump off
#ifdef ENABLE_SERIAL_OUTPUT                   // only output to the serial console if enabled
    Serial.println("Water Pump Setup Complete."); // print status of the setup sequence to serial console
#endif
    // TODO: print setup status to the OLED display
    delay(500); // delay for a tiny bit during the startup process
}

/*
PRINT PUMP STATUS
prints the current status of the pump
*/
void printPumpStatus()
{
#ifdef ENABLE_SERIAL_OUTPUT       // only output to the serial console if enabled
    Serial.print("Water Pump State: "); // print the current state of this realy to the serial console
    Serial.println(pumpCurrentState);

    Serial.print("Total Water Pump Cycles: "); // prints the total amount of times this relay has cycled
    Serial.println(pumpTotalAmountOfCycles);
#endif
    // TODO: print pump state on the oled display
    // TODO: print pump total cycles on the oled display
}

/*
TURN PUMP ON
turns the pump on
*/
void turnPumpOn()
{
    digitalWrite(PUMP_PIN, LOW); // turns the pump on
    pumpCurrentState = true;      // set the flag that tracks state to true
}

/*
TURN PUMP OFF
turns the pump off
*/
void turnPumpOff()
{
    digitalWrite(PUMP_PIN, HIGH); // turns the pump off
    pumpCurrentState = false;    // set the flag that tracks state to false
}

