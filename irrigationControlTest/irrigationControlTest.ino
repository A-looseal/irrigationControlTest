

#pragma region INCLUDES
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h> // Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <millisDelay.h>

#include "src/tools/timeTools.h"
#include "src/settings/testDeviceSettings.h"
#include "src/settings/pumpSettings.h"
#include "src/settings/oxygenSettings.h"
#include "src/settings/whiteLightSettings.h"
#pragma endregion

#pragma region I2C DEVICES
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS3231 rtc;
DateTime now;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#pragma endregion

#pragma region INTERVAL TIMERS
millisDelay testDeviceOnAlarm_A1;
millisDelay testDeviceOffAlarm_A1;
millisDelay pumpOnAlarm_A1;
millisDelay pumpOffAlarm_A1;
millisDelay oxygenOnAlarm_A1;
millisDelay oxygenOffAlarm_A1;
millisDelay whiteLightOnAlarm_A1;
millisDelay whiteLightOffAlarm_A1;
millisDelay redLightOnAlarm_A1;
millisDelay redLightOffAlarm_A1;

millisDelay timer_oled_displayGeneralInfo;
millisDelay timer_oled_displayPumpInfo;
#pragma endregion

// #define RESET_RTC_TIME
//#define ENABLE_SERIAL_OUTPUT // use this line to enable/dissable usage of the SERIAL CONSOLE
#define ENABLE_OLED_OUTPUT // use this line to enable/disable usage of the OLED device

#define ENABLE_TEST_DEVICE // use this line to enable/dissable use of the TEST DEVICE
// #define ENABLE_WATER_PUMP  // use this line to enable/dissable use of the WATER PUMP
// #define ENABLE_OXYGEN_PUMP // use this line to enable/dissable use of the OXYGEN PUMP
// #define ENABLE_WHITE_LIGHT // use this line to enable/dissable use of the WHITE LIGHT
// #define ENABLE_RED_LIGHT      // use this line to enable/dissable use of the RED_LIGHT

#define BAUD_RATE 9600
void setup()
{

  // establish a serial connection at the specified baud rate (9600)
  setupSerialConnection(BAUD_RATE);
  // setup and establish a connection to the OLED DISPLAY
  setupDisplay();
  // setup and establish a connection to the TEST DEVICE
  setupTestDevice();
  // setup and establish a connection to the WATER PUMP
  setupPump();
  // setup and establish a connection to the OXYGEN PUMP
  setupOxygen();
  // setup and establish a connection to the WHITE GROW LIGHTS
  setupWhiteLight();
  // setup and establish a connection to the RTC CLOCK
  setupRTC();

} // END SETUP

void loop()
{
  now = rtc.now(); // get the time from the RTC module
  // oled_displayTime(now); // prints the current time from RTC to the serial console
  // printTemperature_RTC(now);    // prints the current temperature reading from RTC module to the serial console

#ifdef ENABLE_TEST_DEVICE
  testDeviceAlarm();
  oled_displayTestDeviceInfo();
#endif
#ifdef ENABLE_WATER_PUMP
  pumpAlarm();
#endif
#ifdef ENABLE_OXYGEN_PUMP
  oxygenAlarm();
  oled_displayOxygenPumpInfo();
#endif
#ifdef ENABLE_WHITE_LIGHT
  whiteLightAlarm();
#endif

#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
  Serial.println("----------------------------");
  Serial.println("----------------------------");
#endif

  delay(1000);
} // END LOOP

#pragma region STANDARD FUNCTIONS
void setupSerialConnection(int baud)
{
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
  Serial.begin(baud);

#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif
  Serial.println("Serial Connection Established.");
#endif
}

#pragma endregion

#pragma region DEVICE LOGIC FUNCTIONS
//
// WATER PUMP
// checks current time and turns device on if alarm is triggered
void pumpAlarm()
{
  // ALARM 1
  if (enablePumpAlarm_A1 == true)
  {
    if ((now.hour() >= PUMP_ON_HOUR_A1) && (now.hour() <= PUMP_OFF_HOUR_A1)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #1 TRIGGERED! Water Pump");
      Serial.println("Time to turn the pump on!");
#endif
      cyclePumpInterval(PUMP_PIN, PUMP_ON_INTERVAL_A1, PUMP_OFF_INTERVAL_A1); // toggles the specified relay on/off, at the specified on/off interval times
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the pump off!");
#endif
      turnPumpOff();          // explicitly turns the specified device OFF
      isPumpRunning == false; // set relay running state to OFF

      pumpCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }
  // ALARM 2
  if (enablePumpAlarm_A2 == true)
  {
    if ((now.hour() >= PUMP_ON_HOUR_A2) &&
        (now.hour() < PUMP_OFF_HOUR_A2)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #2 TRIGGERED! Water Pump");
      Serial.println("Time to turn the pump on!");
#endif
      cyclePumpInterval(PUMP_PIN, PUMP_ON_INTERVAL_A2, PUMP_OFF_INTERVAL_A2); // toggles the specified relay on/off, at the specified on/off interval times
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the pump off!");
#endif
      turnPumpOff();          // explicitly turns the specified device OFF
      isPumpRunning == false; // set relay running state to OFF

      pumpCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }
  // ALARM 3
  if (enablePumpAlarm_A3 == true)
  {
    if ((now.hour() >= PUMP_ON_HOUR_A3) && (now.hour() < PUMP_OFF_HOUR_A3)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #3 TRIGGERED! Water Pump");
      Serial.println("Time to turn the pump on!");
#endif
      cyclePumpInterval(PUMP_PIN, PUMP_ON_INTERVAL_A3, PUMP_OFF_INTERVAL_A3); // toggles the specified relay on/off, at the specified on/off interval times
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the pump off!");
#endif
      turnPumpOff();          // explicitly turns the specified device OFF
      isPumpRunning == false; // set relay running state to OFF

      pumpCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  if (enablePumpAlarm_A4 == true)
  {
    if ((now.hour() >= PUMP_ON_HOUR_A4) && (now.hour() < PUMP_OFF_HOUR_A4)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #4 TRIGGERED! Water Pump");
      Serial.println("Time to turn the pump on!");
#endif
      cyclePumpInterval(PUMP_PIN, PUMP_ON_INTERVAL_A4, PUMP_OFF_INTERVAL_A4); // toggles the specified relay on/off, at the specified on/off interval times
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the pump off!");
#endif
      turnPumpOff();          // explicitly turns the specified device OFF
      isPumpRunning == false; // set relay running state to OFF

      pumpCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  printPumpStatus();
}
// toggles the device ON/OFF according to the set interval
void cyclePumpInterval(int whichRelay, int onDuration, int offDuration)
{
  isPumpRunning = true;
  int randomNumber = random(50, 500);

  // toggle ON only if it is the first time turning this device on this during this time slot
  if (isPumpFirstCycle == true)
  {
    pumpTotalAmountOfCycles++;
    pumpCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("-----turning pump on. First Cycle-----");
#endif
    // toggle the led
    digitalWrite(whichRelay, HIGH);                   // turn led on
    pumpCurrentState = true;                          // set the flag that tracks relay state to ON
    pumpOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
    isPumpFirstCycle = false;
  }

  // toggle ON if the off interval alarm has timed out
  if (pumpOnAlarm_A1.justFinished() && isPumpFirstCycle == false)
  {
    pumpTotalAmountOfCycles++;
    pumpCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.print("-----turning pump on. Cycle #: ");
#endif
    Serial.print(pumpCurrentAmountOfCycles);
    Serial.println("-----: ");
    // toggle the led
    digitalWrite(whichRelay, HIGH);                   // turn led on
    pumpCurrentState = true;                          // set the flag that tracks relay state to ON
    pumpOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
  }

  // toggle OFF if the on interval alarm has timed out
  if (pumpOffAlarm_A1.justFinished())
  {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("turning pump off.");
#endif
    // toggle the led
    digitalWrite(whichRelay, LOW); // turn led off
    pumpCurrentState = false;      // set the flag that tracks relay state to OFF

    pumpOnAlarm_A1.start(offDuration + randomNumber); // start the timer that tracks when to turn the device ON
  }
}

//
// OXYGEN PUMP
// checks current time and turns device on if alarm is triggered
void oxygenAlarm()
{
  // ALARM 1
  if (enableOxygenAlarm_A1 == true)
  {
    if ((now.hour() >= OXYGEN_ON_HOUR_A1) &&
        (now.hour() <= OXYGEN_OFF_HOUR_A1)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #1 TRIGGERED! Oxygen Pump");
      Serial.println("Time to turn the Oxygen Pump on!");
#endif
      // cycleOxygenInterval(OXYGEN_PIN, OXYGEN_ON_INTERVAL_A1, OXYGEN_OFF_INTERVAL_A1); // toggles the specified relay on/off, at the specified on/off interval times
      turnOxygenOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Oxygen Pump off!");
#endif
      turnOxygenOff();          // explicitly turns the specified device OFF
      isOxygenRunning == false; // set relay running state to OFF

      // oxygenCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 2
  if (enableOxygenAlarm_A2 == true)
  {
    if ((now.hour() >= OXYGEN_ON_HOUR_A2) &&
        (now.hour() <= OXYGEN_OFF_HOUR_A2)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #2 TRIGGERED! Oxygen Pump");
      Serial.println("Time to turn the Oxygen Pump on!");
#endif
      // cycleOxygenInterval(OXYGEN_PIN, OXYGEN_ON_INTERVAL_A2, OXYGEN_OFF_INTERVAL_A2); // toggles the specified relay on/off, at the specified on/off interval times
      turnOxygenOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Oxygen Pump off!");
#endif
      turnOxygenOff();          // explicitly turns the specified device OFF
      isOxygenRunning == false; // set relay running state to OFF

      // oxygenCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 3
  if (enableOxygenAlarm_A3 == true)
  {
    if ((now.hour() >= OXYGEN_ON_HOUR_A3) &&
        (now.hour() <= OXYGEN_ON_HOUR_A3)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #3 TRIGGERED! Oxygen Pump");
      Serial.println("Time to turn the Oxygen Pump on!");
#endif
      // cycleOxygenInterval(OXYGEN_PIN, OXYGEN_OFF_INTERVAL_A3, OXYGEN_OFF_INTERVAL_A3); // toggles the specified relay on/off, at the specified on/off interval times
      turnOxygenOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Oxygen Pump off!");
#endif
      turnOxygenOff();          // explicitly turns the specified device OFF
      isOxygenRunning == false; // set relay running state to OFF

      // oxygenCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  printOxygenStatus();
}
// toggles the device ON/OFF according to the set interval
void cycleOxygenInterval(int whichRelay, int onDuration, int offDuration)
{
  isOxygenRunning = true;
  int randomNumber = random(50, 500);

  // toggle ON only if it is the first time turning this device on this during this time slot
  if (isOxygenFirstCycle == true)
  {
    oxygenTotalAmountOfCycles++;
    oxygenCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("-----Turning Oxygen Pump on. First Cycle-----");
#endif
    turnOxygenOn();                                     // togle the device ON
    oxygenOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
    isOxygenFirstCycle = false;
  }

  // toggle ON if the off interval alarm has timed out
  if (oxygenOnAlarm_A1.justFinished() && isOxygenFirstCycle == false)
  {
    oxygenTotalAmountOfCycles++;
    oxygenCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.print("-----Turning Oxygen Pump on. Cycle #: ");
    Serial.print(oxygenCurrentAmountOfCycles);
    Serial.println("-----: ");
#endif

    turnOxygenOn();                                     // toggle the device ON
    oxygenOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
  }

  // toggle OFF if the on interval alarm has timed out
  if (oxygenOffAlarm_A1.justFinished())
  {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("Turning Oxygen Pump off.");
#endif

    turnOxygenOff(); // toggle the device OFF

    oxygenOnAlarm_A1.start(offDuration + randomNumber); // start the timer that tracks when to turn the device ON
  }
}

//
// WHITE LIGHT
// checks current time and turns device on if alarm is triggered
void whiteLightAlarm()
{
  // ALARM 1
  if (enableWhiteLightAlarm_A1 == true)
  {
    if ((now.hour() >= WHITE_LIGHT_ON_HOUR_A1) &&
        (now.hour() < WHITE_LIGHT_OFF_HOUR_A1)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #1 TRIGGERED! White Light");
      Serial.println("Time to turn the White Light on!");
#endif
      // cycleWhiteLightInterval(WHITE_LIGHT_PIN, WHITE_LIGHT_ON_INTERVAL_A1, WHITE_LIGHT_OFF_INTERVAL_A1); // toggles the specified relay on/off, at the specified on/off interval times
      turnWhiteLightOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the White Light off!");
#endif
      turnWhiteLightOff();          // explicitly turns the specified device OFF
      isWhiteLightRunning == false; // set relay running state to OFF

      whiteLightCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 2
  if (enableWhiteLightAlarm_A2 == true)
  {
    if ((now.hour() >= WHITE_LIGHT_ON_HOUR_A2) &&
        (now.hour() < WHITE_LIGHT_OFF_HOUR_A2)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #2 TRIGGERED! White Light");
      Serial.println("Time to turn the White Light on!");
#endif
      // cycleWhiteLightInterval(WHITE_LIGHT_PIN, WHITE_LIGHT_ON_INTERVAL_A2, WHITE_LIGHT_OFF_INTERVAL_A2); // toggles the specified relay on/off, at the specified on/off interval times
      turnWhiteLightOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the White Light off!");
#endif
      turnWhiteLightOff();          // explicitly turns the specified device OFF
      isWhiteLightRunning == false; // set relay running state to OFF

      whiteLightCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 3
  if (enableWhiteLightAlarm_A3 == true)
  {
    if ((now.hour() >= WHITE_LIGHT_ON_HOUR_A3) &&
        (now.hour() < WHITE_LIGHT_OFF_HOUR_A3)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #3 TRIGGERED! White Light");
      Serial.println("Time to turn the White Light on!");
#endif
      // cycleWhiteLightInterval(PUMP_PIN, WHITE_LIGHT_ON_INTERVAL_A3, WHITE_LIGHT_OFF_INTERVAL_A3); // toggles the specified relay on/off, at the specified on/off interval times
      turnWhiteLightOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the White Light off!");
#endif
      turnWhiteLightOff();          // explicitly turns the specified device OFF
      isWhiteLightRunning == false; // set relay running state to OFF

      whiteLightCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  printWhiteLightStatus();
}
// toggles the device ON/OFF according to the set interval
void cycleWhiteLightInterval(int whichRelay, int onDuration, int offDuration)
{
  isWhiteLightRunning = true;
  int randomNumber = random(50, 500);

  // toggle ON only if it is the first time turning this device on this during this time slot
  if (isWhiteLightFirstCycle == true)
  {
    whiteLightTotalAmountOfCycles++;
    whiteLightCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("-----Turning White Light on. First Cycle-----");
#endif
    // toggle the led
    turnWhiteLightOn();                                     // toggle the device ON
    whiteLightOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
    isWhiteLightFirstCycle = false;
  }

  // toggle ON if the off interval alarm has timed out
  if (whiteLightOnAlarm_A1.justFinished() && isWhiteLightFirstCycle == false)
  {
    whiteLightTotalAmountOfCycles++;
    whiteLightCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.print("-----Turning White Light on. Cycle #: ");
    Serial.print(whiteLightCurrentAmountOfCycles);
    Serial.println("-----: ");
#endif

    turnWhiteLightOn();                                     // toggle the device ON
    whiteLightOffAlarm_A1.start(onDuration + randomNumber); // start the timer that tracks when to turn the device OFF
  }

  // toggle OFF if the on interval alarm has timed out
  if (whiteLightOffAlarm_A1.justFinished())
  {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("Turning White Light off.");
#endif

    turnWhiteLightOff();                                    // toggle the device OFF
    whiteLightOnAlarm_A1.start(offDuration + randomNumber); // start the timer that tracks when to turn the device ON
  }
}

//
// TEST DEVICE
// checks current time and turns device on if alarm is triggered
void testDeviceAlarm()
{
  // ALARM 1
  if (enableTestDeviceAlarm_A1 == true)
  {
    if ((now.hour() >= TEST_DEVICE_ON_HOUR_A1) &&
        (now.hour() <= TEST_DEVICE_OFF_HOUR_A1)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #1 TRIGGERED! Test Device");
      Serial.println("Time to turn the Test Device on!");
#endif
      cycleTestDeviceInterval(TEST_DEVICE_PIN, TEST_DEVICE_ON_INTERVAL_A1, TEST_DEVICE_OFF_INTERVAL_A1); // toggles the specified relay on/off, at the specified on/off interval times
      // turnTestDeviceOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Test Device off!");
#endif
      turnTestDeviceOff();          // explicitly turns the specified device OFF
      isTestDeviceRunning == false; // set relay running state to OFF

      testDeviceCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 2
  if (enableTestDeviceAlarm_A2 == true)
  {
    if ((now.hour() >= TEST_DEVICE_ON_HOUR_A2) &&
        (now.hour() <= TEST_DEVICE_OFF_HOUR_A2)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #2 TRIGGERED! Test Device");
      Serial.println("Time to turn the Test Device on!");
#endif
      // cycleTestDeviceInterval(TEST_DEVICE_PIN, TEST_DEVICE_ON_INTERVAL_A2, TEST_DEVICE_OFF_INTERVAL_A2); // toggles the specified relay on/off, at the specified on/off interval times
      turnTestDeviceOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Test Device off!");
#endif
      turnTestDeviceOff();          // explicitly turns the specified device OFF
      isTestDeviceRunning == false; // set relay running state to OFF

      testDeviceCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  // ALARM 3
  if (enableTestDeviceAlarm_A3 == true)
  {
    if ((now.hour() >= TEST_DEVICE_ON_HOUR_A3) &&
        (now.hour() <= TEST_DEVICE_OFF_HOUR_A3)) // turn the specified device ON at the specified time
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("ALARM #3 TRIGGERED! Test Device");
      Serial.println("Time to turn the Test Device on!");
#endif
      // cycleTestDeviceInterval(TEST_DEVICE_PIN, TEST_DEVICE_ON_INTERVAL_A3, TEST_DEVICE_OFF_INTERVAL_A3); // toggles the specified relay on/off, at the specified on/off interval times
      turnTestDeviceOn();
    }
    else
    {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
      Serial.println("Time to turn the Test Device off!");
#endif
      turnTestDeviceOff();          // explicitly turns the specified device OFF
      isTestDeviceRunning == false; // set relay running state to OFF

      testDeviceCurrentAmountOfCycles = 0; // reset cycle counter
    }
  }

  printTestDeviceStatus();
}
// toggles the device ON/OFF according to the set interval
void cycleTestDeviceInterval(int whichRelay, int onDuration, int offDuration)
{
  isTestDeviceRunning = true;
  int randomNumber = random(50, 500);

  // toggle ON only if it is the first time turning this device on this during this time slot
  if (isTestDeviceFirstCycle == true)
  {
    testDeviceTotalAmountOfCycles++;
    testDeviceCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("-----Turning Test Device on. First Cycle-----");
#endif
    // toggle the led
    turnTestDeviceOn();                                                                  // toggle the device ON
    testDeviceOffAlarm_A1.start(convertMinuteToMilliseconds(onDuration) + randomNumber); // start the timer that tracks when to turn the device OFF
    isTestDeviceFirstCycle = false;
  }

  // toggle ON if the off interval alarm has timed out
  if (testDeviceOnAlarm_A1.justFinished() && isTestDeviceFirstCycle == false)
  {
    testDeviceTotalAmountOfCycles++;
    testDeviceCurrentAmountOfCycles++;
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.print("-----Turning Test Device on. Cycle #: ");
    Serial.print(testDeviceCurrentAmountOfCycles);
    Serial.println("-----: ");
#endif

    turnTestDeviceOn();                                                                  // toggle the device ON
    testDeviceOffAlarm_A1.start(convertMinuteToMilliseconds(onDuration) + randomNumber); // start the timer that tracks when to turn the device OFF
  }

  // toggle OFF if the on interval alarm has timed out
  if (testDeviceOffAlarm_A1.justFinished())
  {
#ifdef ENABLE_SERIAL_OUTPUT // only output to the serial console if enabled
    Serial.println("Turning Test Device off.");
#endif

    turnTestDeviceOff();                                                                 // toggle the device OFF
    testDeviceOnAlarm_A1.start(convertMinuteToMilliseconds(offDuration) + randomNumber); // start the timer that tracks when to turn the device ON
  }
}

#pragma endregion

#pragma region I2C DEVICE SETUP
// SETUP OLED DISPLAY
void setupDisplay()
{
#ifdef ENABLE_OLED_OUTPUT
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  Serial.println("OLED Setup Complete.");
#endif
}
// SETUP RTC CLOCK
void setupRTC()
{
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1)
      delay(10);
  }
  else
  {
    Serial.println("RTC Setup Complete.");
  }

// When time needs to be re-set on a previously configured device, the
// following line sets the RTC to the date & time this sketch was compiled
#ifdef RESET_RTC_TIME
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("RTC has been updated with a new Date and Time! Be Careful!");
#endif
}

// PRINT TIME
void oled_displayTime(DateTime now, char xPos, char yPos)
{
#ifdef ENABLE_OLED_OUTPUT
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(xPos, yPos);       // Start at top-left corner
  // display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  // display.print(" ");
  display.print(now.hour(), DEC);
  display.print(":");
  display.print(now.minute(), DEC);
  display.print(":");
  display.print(now.second(), DEC);
#endif
}

// TEMPERATURE
void oled_displayTemperature(DateTime now, char xPos, char yPos)
{
#ifdef ENABLE_OLED_OUTPUT
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(xPos, yPos);       // Start at top-left corner
  // display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  // display.print(" ");
  display.print(rtc.getTemperature(), DEC);
  display.print(":");
#endif
}

#pragma endregion

#pragma region DEVICE OLED OUTPUT
// output to display
void oled_displayTestDeviceInfo()
{
#ifdef ENABLE_OLED_OUTPUT // only output to the oled display if enabled in the config
  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

  // draw current device name on the display
  display.setCursor(0, 0); // Start at top-left corner
  display.println("TEST DEVICE");

  if (testDeviceCurrentState == LOW) // LOW = FALSE = OFF = 0
  {
    display.setCursor(110, 0); // Start at top-left corner
    display.println("OFF");
  }
  if (testDeviceCurrentState == HIGH) // HIGH = TRUE = ON = 1
  {
    display.setCursor(110, 0); // Start at top-left corner
    display.println("ON");
  }

  // draw device current alarm state on the display
  if (isTestDeviceRunning == HIGH) // HIGH = TRUE = ON = 1
  {
    display.setCursor(0, 10); // Start at top-left corner
    display.println("Active");
    // TODO: device current relay state
  }
  else
  {
    display.setCursor(0, 10); // Start at top-left corner
    display.println("Inactive");
  }

  // draw device current cycle count to the oled display
  display.setCursor(70, 10); // Start at top-left corner
  display.print("Cycle: ");
  display.println(testDeviceTotalAmountOfCycles);

  oled_displayTime(now, 0, 25);

  display.display();
#endif
}

#pragma endregion