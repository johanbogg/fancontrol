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

unsigned long interval=1000;
unsigned long previousMillis=0;
unsigned long previousMillisDisplay=0;
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
int newfanMode;

char version[] = "0.1.20190308";
char *fanGfx[] = {"- - -","* - -","* * -","* * *"};
char *Modes[] = {"Summer","Winter","Manual"};

/********************************************************************/
OneWire oneWire(ONE_WIRE_BUS);
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/********************************************************************/
DallasTemperature sensors(&oneWire);

/********************************************************************/
int iterations=0;
long maxiterations=30;

int LOW_SPDPIN = 5;
int MID_SPDPIN = 6;
int HIGH_SPDPIN = 7;
int UP_BTN = 18;
int DWN_BTN = 19;
int SEL_BTN = 20;

// EEPROM Save addresses:
uint8_t LOWTMP_EEPROM=32;
uint8_t MIDTMP_EEPROM=34;
uint8_t HIGHTMP_EEPROM=36;
uint8_t MAXITER_EEPROM=40;

float lowTemp = EEPROM.read(LOWTMP_EEPROM);
float midTemp = EEPROM.read(MIDTMP_EEPROM);
float highTemp = EEPROM.read(HIGHTMP_EEPROM);

int menuSelVal=0;

DeviceAddress Sensor1 = {0x28,0xFF,0x04,0x6A,0x80,0x16,0x03,0x1A};
DeviceAddress Sensor2 = {0x28,0xFF,0x9B,0x69,0x80,0x16,0x03,0x4A};

void setup(void)
{
  // Relay pins active-HIGH: set LOW (off) before OUTPUT to avoid glitch
  digitalWrite(LOW_SPDPIN, LOW);
  digitalWrite(MID_SPDPIN, LOW);
  digitalWrite(HIGH_SPDPIN, LOW);

  pinMode(LOW_SPDPIN, OUTPUT);
  pinMode(MID_SPDPIN, OUTPUT);
  pinMode(HIGH_SPDPIN, OUTPUT);
  pinMode(UP_BTN, INPUT);
  pinMode(DWN_BTN, INPUT);
  pinMode(SEL_BTN, INPUT);

  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();
  sensors.begin();
  sensors.setResolution(Sensor1, 10);
  sensors.setResolution(Sensor2, 10);
  sensors.setWaitForConversion(true);
  display.setRotation(2);

  maxiterations = EEPROMReadlong(MAXITER_EEPROM);
  if (maxiterations <= 0 || maxiterations > 3600) maxiterations = 30; // guard against blank EEPROM

  // Run checkTemp immediately on boot instead of waiting maxiterations seconds
  iterations = maxiterations;
}

void loop(void)
{
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    sensors.requestTemperatures();
    tempSensor1 = sensors.getTempC(Sensor1);
    tempSensor2 = sensors.getTempC(Sensor2);

    if (iterations >= maxiterations) {
      checkTemp(tempSensor1, tempSensor2, lowTemp);
      iterations = 0;
    }

    updateSerial(tempSensor1, tempSensor2, fanMode);
    iterations++;
    previousMillis = millis();
  }

  // Update screen and check buttons every 100ms, independently of the 1s sensor loop
  if ((unsigned long)(currentMillis - previousMillisDisplay) >= 100) {
    updateScreen(tempSensor1, tempSensor2, fanMode);
    chkBtns();
    previousMillisDisplay = currentMillis;
  }
}
