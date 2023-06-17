#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <DFRobot_SIM808.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
// #include <sim808.h>

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(
    128, 64, &Wire,
    -1);  // (width, height, wire, reset pin (-1 share Arduino reset))

SoftwareSerial BTserial(10, 11);  // RX | TX

const int DIN_2 = 2;  // lev 1
const int DIN_3 = 3;  // lev 2
const int DIN_4 = 4;  // lev 3
const int DIN_5 = 5;  // lev 4
const int DIN_6 = 6;  // lev 5
const int DIN_7 = 7;  // lev 6
const int DIN_8 = 8;  // waste full

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  // set digital pins
  pinMode(DIN_2, INPUT);
  pinMode(DIN_3, INPUT);
  pinMode(DIN_4, INPUT);
  pinMode(DIN_5, INPUT);
  pinMode(DIN_6, INPUT);
  pinMode(DIN_7, INPUT);
  pinMode(DIN_8, INPUT);

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  int LVL_1 = digitalRead(DIN_2);  // detect the status of the pin
  int LVL_2 = 1;                   // digitalRead(DIN_3);
  int LVL_3 = 1;                   // digitalRead(DIN_4);
  int LVL_4 = 1;                   // digitalRead(DIN_5);
  int LVL_5 = 0;                   // digitalRead(DIN_6);
  int LVL_6 = 0;                   // digitalRead(DIN_7);
  int WASTE_FULL = 0;              // digitalRead(DIN_8);
  // Serial.println(LVL_1);

  // send data by Bluetooth
  BTserial.print(LVL_1);
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(",");
  BTserial.print("null");
  BTserial.print(";");

  // markers
  display.setRotation(3);
  display.setCursor(4, 90);
  display.println("1-");
  display.setCursor(4, 72);
  display.println("2-");
  display.setCursor(4, 55);
  display.println("3-");
  display.setCursor(4, 38);
  display.println("4-");
  display.setCursor(4, 20);
  display.println("5-");
  display.setCursor(4, 3);
  display.println("6-");
  display.setTextColor(WHITE, BLACK);

  // level bars
  display.display();
  if (LVL_6 == 1) {
    display.fillRect(20, 0, 40, 15, WHITE);
  } else {
    display.drawRect(20, 0, 40, 15, WHITE);
  }

  if (LVL_5 == 1) {
    display.fillRect(20, 17, 40, 15, WHITE);
  } else {
    display.drawRect(20, 17, 40, 15, WHITE);
  }

  if (LVL_4 == 1) {
    display.fillRect(20, 34, 40, 15, WHITE);
  } else {
    display.drawRect(20, 34, 40, 15, WHITE);
  }

  if (LVL_3 == 1) {
    display.fillRect(20, 51, 40, 15, WHITE);
  } else {
    display.drawRect(20, 51, 40, 15, WHITE);
  }

  if (LVL_2 == 1) {
    display.fillRect(20, 68, 40, 15, WHITE);
  } else {
    display.drawRect(20, 68, 40, 15, WHITE);
  }

  if (LVL_1 == 1) {
    display.fillRect(20, 85, 40, 15, WHITE);
  } else {
    display.drawRect(20, 85, 40, 15, WHITE);
  }

  // display.display();
  // display.clearDisplay();

  delay(5000);
}