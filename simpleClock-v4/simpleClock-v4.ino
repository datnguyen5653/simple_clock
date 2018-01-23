
/*
   testing DS 1307 RTC module
   set time function
   using Adafruit library
   @ Author( Dat nguyen )
   Date(jan 13th , 2018)
   Last Date Modified: jan 13rd,2018
   All right reserved to Dat Nguyen
   Copy right

   This program show a simple clock using RTC DS 1307 module
   require 3 push button. ( up, down, menu)
   one can display and change the time and date of the RTC.
  V2
   added:
   humid sensor
   Alarm
   source:
    http://mikeyancey.com/hamcalc/lcd_characters.php
    http://www.tehnic.go.ro 
    http://nicuflorica.blogspot.ro
*/

/*Include library*/
#include<Wire.h>
#include<RTClib.h>
#include<dht.h>
#include<Pushbutton.h>
#include<EEPROM.h>
#include<LiquidCrystal_I2C.h>
#include<CapacitiveSensor.h>


#define LDR_PIN A0
#define MOSFET_PIN 3
#define DHT11_PIN 4
#define BUZZER_PIN 6
#define I2C_ADDR 0x27
#define SEND_PIN 10 //  capacitive send pin 
#define FRONT_PIN 8
#define OK_PIN 9
#define UP_PIN 11
#define DOWN_PIN 12


/*Initiallize object*/
CapacitiveSensor _frontButton = CapacitiveSensor(SEND_PIN,FRONT_PIN);
CapacitiveSensor _okButton = CapacitiveSensor(SEND_PIN,OK_PIN);
CapacitiveSensor _upButton = CapacitiveSensor(SEND_PIN,UP_PIN);
CapacitiveSensor _downButton = CapacitiveSensor(SEND_PIN,DOWN_PIN);
RTC_DS1307 RTC;
dht DHT;
LiquidCrystal_I2C lcd(I2C_ADDR,16,2);

/* global Variable */
uint8_t currentHour, currentMin, currentSec, currentMonth, currentDay ; 
uint16_t currentYear ;  
uint32_t frontButton, okButton, upButton, downButton;

// define 8 bar array form each segment of the custom number for lcd 16 x2 display

byte bar1[8] = {B11100,B11110,B11110,B11110,B11110,B11110,B11110,B11100};
byte bar2[8] ={B00111,B01111,B01111,B01111,B01111,B01111,B01111,B00111};
byte bar3[8] ={B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar4[8] ={B11110,B11100,B00000,B00000,B00000,B00000,B11000,B11100};
byte bar5[8] ={B01111,B00111,B00000,B00000,B00000,B00000,B00011,B00111};
byte bar6[8] ={B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar7[8] ={B00000,B00000,B00000,B00000,B00000,B00000,B00111,B01111};
byte bar8[8] ={B11111,B11111,B00000,B00000,B00000,B00000,B00000,B00000};

// create custom Character for display
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t option[8] ={0,18,0x3C,13,13,0x3C,18,0};


/** these function create custom big font number display on lcd 16x2*/
void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom4(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}


