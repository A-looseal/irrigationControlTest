#include "whiteLightSettings.h"
#define ENABLE_SERIAL_OUTPUT

#pragma region VARIABLES
// PUMP SETTINGS
#define WHITE_LIGHT_PIN 4           // gpio pin relay is connected to
bool whiteLightCurrentState = false;     // state of the relay when it is currently time to be on
bool isWhiteLightRunning = false; // is it currently time for the relay to be on
bool isWhiteLightFirstCycle = true;    // is this the first time relay is on during this time slot
int whiteLightTotalAmountOfCycles;
int whiteLightCurrentAmountOfCycles;

// PUMP ALARM SETTINGS
bool enableWhiteLightAlarm_A1 = true;
bool enableWhiteLightAlarm_A2 = false;
bool enableWhiteLightAlarm_A3 = false;
#pragma endregion

/*
SETUP PUMP
initializes the pump and performs all setup housekeeping
*/
void setupWhiteLight()
{
    pinMode(WHITE_LIGHT_PIN, OUTPUT);                // initializes the GPIO as an OUTPUT
    digitalWrite(WHITE_LIGHT_PIN, HIGH); // turns the pump off
#ifdef ENABLE_SERIAL_OUTPUT                   // only output to the serial console if enabled
    Serial.println("White Light Setup Complete."); // print status of the setup sequence to serial console
#endif
    // TODO: print setup status to the OLED display
    delay(500); // delay for a tiny bit during the startup process
}

/*
PRINT PUMP STATUS
prints the current status of the pump
*/
void printWhiteLightStatus()
{
#ifdef ENABLE_SERIAL_OUTPUT       // only output to the serial console if enabled
    Serial.print("White Light State: "); // print the current state of this realy to the serial console
    Serial.println(whiteLightCurrentState);

    Serial.print("White Light Total Cycles: "); // prints the total amount of times this relay has cycled
    Serial.println(whiteLightTotalAmountOfCycles);
#endif
    // TODO: print pump state on the oled display
    // TODO: print pump total cycles on the oled display
}

/*
TURN PUMP ON
turns the pump on
*/
void turnWhiteLightOn()
{
    digitalWrite(WHITE_LIGHT_PIN, LOW); // turns the pump on
    whiteLightCurrentState = true;      // set the flag that tracks state to true
}

/*
TURN PUMP OFF
turns the pump off
*/
void turnWhiteLightOff()
{
    digitalWrite(WHITE_LIGHT_PIN, HIGH); // turns the pump off
    whiteLightCurrentState = false;    // set the flag that tracks state to false
}

