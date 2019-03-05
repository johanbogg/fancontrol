/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

/********************************************************************/
// Data wire for one-wire ds18b20s connected to this pin 
#define ONE_WIRE_BUS 8 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// I know public/global variables aren't exactly the safest approach
// But let's do it like this until refactored...

unsigned long interval=1000;
unsigned long previousMillis=0;
int fanMode=0;
int heatMode=1; // WinterMode is default, will not save to EEPROM!

int selBtnstate = 0;
int dwnBtnstate = 0;
int upBtnstate = 0;
int oldselBtnstate = 0;
int olddwnBtnstate = 0;
int oldupBtnstate = 0;
int settingsChanged = 0;
float tempSensor1;
float tempSensor2;
int displayMode=0;

char version[] = "0.1.20190304";
char *fanGfx[] = {"- - -","* - -","* * -","* * *"};
char *Modes[] = {"Summer","Winter","Manual"};
// Set up Pins for Relays
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 

OneWire oneWire(ONE_WIRE_BUS); 
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 

DallasTemperature sensors(&oneWire);

/********************************************************************/ 
// Set iterations to 0 and initiate maxiterations 
// maxiterations will be read from EEPROM.
// Will loop for approx <maxiterations> seconds before adjusting fans
// Adjust to get it to not react to fast to temperature change

int iterations=0;
long maxiterations=30;

int LOW_SPDPIN = 5; // Pin for Low speed fan relay
int MID_SPDPIN = 6; // Pin for Mid speed fan relay
int HIGH_SPDPIN = 7; // Pin for High speed fan relay
int UP_BTN = 18; // Pin for UP BTN
int DWN_BTN = 19; // Pin for DWN BTN
int SEL_BTN = 20; // Pin for SEL BTN


// EEPROM Save addresses:
uint8_t LOWTMP_EEPROM=32;
uint8_t MIDTMP_EEPROM=34;
uint8_t HIGHTMP_EEPROM=36;
uint8_t MAXITER_EEPROM=40;



// When water temperature less than lowTemp it will shut down the fan
// Adjust here to desired value
// midTemp = Water temperature to adjust fan to mid speed 
// highTemp = Water temperature to adjust fan to high speed 


float lowTemp = EEPROM.read(LOWTMP_EEPROM);
float midTemp = EEPROM.read(MIDTMP_EEPROM);
float highTemp = EEPROM.read(HIGHTMP_EEPROM);

// Default to first value in menu

int menuSelVal=0;

// Sensor addresses for Sensor1 (Water) and Sensor2 (Air)
 
DeviceAddress Sensor1 = {0x28,0xFF,0x04,0x6A,0x80,0x16,0x03,0x1A};
DeviceAddress Sensor2 = {0x28,0xFF,0x9B,0x69,0x80,0x16,0x03,0x4A};


 
void setup(void) 
{ 
maxiterations=30;
//EEPROMReadlong(MAXITER_EEPROM);

//Set the relay pins to high first
//then initialize as output, as pins otherwise defaults to low
//Relay pulls at low, so...just a precaution.

digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);

// Set pins to digital output

pinMode(LOW_SPDPIN, OUTPUT);
pinMode(MID_SPDPIN, OUTPUT);
pinMode(HIGH_SPDPIN, OUTPUT);
pinMode(UP_BTN, INPUT);
pinMode(DWN_BTN, INPUT);
pinMode(SEL_BTN, INPUT);

 // start serial port 
 Serial.begin(9600); 
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();
 // Start up the library 
 sensors.begin(); 

 // Resolution 10 = 0.25 increments, enough for us
 sensors.setResolution(Sensor1, 10);
 sensors.setResolution(Sensor2, 10);
 
 // Wait for sensor to correctly adjust to reading
 sensors.setWaitForConversion(true);
 display.setRotation(2);
} 
void loop(void) 
{ 
 unsigned long currentMillis = millis();
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 if ((unsigned long)(currentMillis - previousMillis) >= interval) {

 sensors.requestTemperatures(); // Send the command to get temperature readings 

 
/******************************************************************/
// Collect the temperatures
// Collect the temperatures
// tempSensor1 = Water temperature
// tempSensor2 = Air temperature

 tempSensor1 = sensors.getTempC(Sensor1);
 tempSensor2 = sensors.getTempC(Sensor2); 
 
// Start if statements to check temperature
 if (iterations >= maxiterations) {
  
  checkTemp(tempSensor1,tempSensor2,lowTemp); //Only update fan-speed every maxiterations*1000 millis.
  iterations=0;
  }
 

 //updateScreen(tempSensor1, tempSensor2, fanMode);
 updateSerial(tempSensor1, tempSensor2, fanMode);
  iterations++;


 //delay(1000);

 previousMillis=millis();
// End if statements to check temperature
}
 
 // Update screen and check buttons every 1/10th of a second.
 else if ((unsigned long)(currentMillis - previousMillis) >= 100) {
 updateScreen(tempSensor1,tempSensor2,fanMode);
 chkBtns();
 
 
 }
}
