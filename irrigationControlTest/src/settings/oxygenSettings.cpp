#include "oxygenSettings.h"
#define ENABLE_SERIAL_OUTPUT

#pragma region VARIABLES
// PUMP SETTINGS
#define OXYGEN_PIN 3           // gpio pin relay is connected to
bool oxygenCurrentState = false;     // state of the relay when it is currently time to be on
bool isOxygenRunning = false; // is it currently time for the relay to be on
bool isOxygenFirstCycle = true;    // is this the first time relay is on during this time slot
int oxygenTotalAmountOfCycles;
int oxygenCurrentAmountOfCycles;

// PUMP ALARM SETTINGS
bool enableOxygenAlarm_A1 = true;
bool enableOxygenAlarm_A2 = true;
bool enableOxygenAlarm_A3 = false;
#pragma endregion

/*
SETUP PUMP
initializes the pump and performs all setup housekeeping
*/
void setupOxygen()
{
    pinMode(OXYGEN_PIN, OUTPUT);                // initializes the GPIO as an OUTPUT
    digitalWrite(OXYGEN_PIN, HIGH); // turns the pump off
#ifdef ENABLE_SERIAL_OUTPUT                   // only output to the serial console if enabled
    Serial.println("Oxygen Pump Setup Complete."); // print status of the setup sequence to serial console
#endif
    // TODO: print setup status to the OLED display
    delay(500); // delay for a tiny bit during the startup process
}

/*
PRINT PUMP STATUS
prints the current status of the pump
*/
void printOxygenStatus()
{
#ifdef ENABLE_SERIAL_OUTPUT       // only output to the serial console if enabled
    Serial.print("Oxygen Pump State: "); // print the current state of this realy to the serial console
    Serial.println(oxygenCurrentState);

    Serial.print("Oxygen Pump Total Cycles: "); // prints the total amount of times this relay has cycled
    Serial.println(oxygenTotalAmountOfCycles);
#endif
    // TODO: print pump state on the oled display
    // TODO: print pump total cycles on the oled display
}

/*
TURN PUMP ON
turns the pump on
*/
void turnOxygenOn()
{
    digitalWrite(OXYGEN_PIN, LOW); // turns the pump on
    oxygenCurrentState = true;      // set the flag that tracks state to true
}

/*
TURN PUMP OFF
turns the pump off
*/
void turnOxygenOff()
{
    digitalWrite(OXYGEN_PIN, HIGH); // turns the pump off
    oxygenCurrentState = false;    // set the flag that tracks state to false
}

