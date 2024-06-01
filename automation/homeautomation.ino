#include <Wire.h>
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
#include <SparkFun_APDS9960.h>
#define APDS9960_INT 2
//SparkFun_APDS9960 apds = SparkFun_APDS9960();
#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, A0, A1, A2, A3);
#include <SoftwareSerial.h>
SoftwareSerial bt(7, 8);  // (Rx,Tx)
String c;
String Incoming_value;

void setup() {
  Serial.begin(9600);  // the  baud rate
  bt.begin(9600);
  pinMode(APDS9960_INT, INPUT);
  if (!apds.begin()) {
    Serial.println("failed to initialize device! Please check your wiring.");
  } else Serial.println("Device initialized!");

  //gesture mode will be entered once proximity mode senses something close
  apds.enableProximity(true);
  apds.enableGesture(true);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("CONTACTLESS ^$");
  lcd.setCursor(0, 1);
  lcd.print("HOME AUTOMATION");
  delay(1500);
  pinMode(4, OUTPUT);  // bulb
  pinMode(5, OUTPUT);  // fan
  digitalWrite(4, HIGH);
  digitalWrite(5,HIGH);
}



void loop() {
   uint8_t gesture = apds.readGesture();
  if (gesture == APDS9960_DOWN) {
    bt.println("v");
    digitalWrite(4, HIGH);
    bt.println("LIGHT OFF");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("v");
    lcd.setCursor(0, 1);
    lcd.print("LIGHT OFF");
  }
  if (gesture == APDS9960_UP) {
    bt.println("^");
    digitalWrite(4, LOW);
    bt.println("LIGHT ON");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("^");
    lcd.setCursor(0, 1);
    lcd.print("LIGHT ON ");
  }
  if (gesture == APDS9960_LEFT) {
    bt.println("<");
    digitalWrite(5, HIGH);
    bt.println("FAN OFF");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(0, 1);
    lcd.print("FAN OFF");
  }
  if (gesture == APDS9960_RIGHT) {
    bt.println(">");
    digitalWrite(5, LOW);
    bt.println("Fan ON");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(0, 1);
    lcd.print("FAN ON");
  }
  String data = "";
  char ch;
  while (bt.available())  //If data is available on serial port
  {
    ch = bt.read();  //Print character received on to the serial monitor
    data = data + ch;
  }
  if (data == "light off") {
    digitalWrite(4, HIGH);
    bt.println("LIGHT OFF");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("BY Bluetooth");
    lcd.setCursor(0, 1);
    lcd.print("BULB OFF");
  }
  if (data == "light on") {
    digitalWrite(4, LOW);
    bt.println("LIGHT ON");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("BY Bluetooth");
    lcd.setCursor(0, 1);
    lcd.print("LIGHT ON ");
  }
  if (data == "fan off") {
    digitalWrite(5, HIGH);
    bt.println("Fan OFF");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("BY Bluetooth");
    lcd.setCursor(0, 1);
    lcd.print("FAN OFF");
  }
  if (data == "fan on") {
    digitalWrite(5, LOW);
    bt.println("Fan ON");
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("BY Bluetooth");
    lcd.setCursor(0, 1);
    lcd.print("FAN ON");
  }
}
