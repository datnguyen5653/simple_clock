
/*
   testing DS 1307 RTC module
   set time function
   using Adafruit library
   @ Author( Dat nguyen )
   Date(jan 13rd , 2018)
   Last Date Modified: jan 13rd,2018
   All right reserved to Dat Nguyen
   Copy right

   This program show a simple clock using RTC DS 1307 module
   require 3 push button. ( up, down, menu)
   one can display and change the time and date of the RTC.
*/

#include<Wire.h>
#include<RTClib.h>

#include<Pushbutton.h>

Pushbutton upButton(4);
Pushbutton downButton(2);
Pushbutton menuButton(3);

/* global Variable */
int menu = 0;
int setHour, setMin, setDay, setMonth, setYear;

String monthName[12] = {"Jan", "Feb","Mar","April","May","Jun","Jul","April",
                      "Sept","Oct","Nov","Dec"};

RTC_DS1307 RTC;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) { // check if the RTC modulke is running
    Serial.println("RTC is NOT running ");
    RTC.adjust(DateTime(__DATE__, __TIME__)); // set date and time at compile time
  }
  int menu = 0; // initialize at home page
}// end setup()



void loop() {

//
  if (menuButton.getSingleDebouncedPress()) {
    menu = menu + 1 ;
    Serial.println("menu add 1");
  }
  delay(50);

// menu User interface.
// Time setting 
  if (menu == 0) {
    Serial.println("menu 0");
    showDateTime();
  }
  if (menu == 1) {
    Serial.println("menu 1");
    showHour();
  }
  if (menu == 2) {
    Serial.println("menu 2");
    showMin();
  }
  /* Date Setting*/
  if (menu == 3) {
    Serial.println("menu 3");
    showDay();
  } if (menu == 4) {
    Serial.println("menu 4");
    showMonth();
  }  if (menu == 5) {
    Serial.println("menu 5");
    showYear();
  } 
  
  if (menu == 6) {
    Serial.println("menu 6");
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
    //DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
    delay(300);
    menu = 0;
  }



}// end loop()

void showDateTime() {
  Serial.println("showing time");

 /*Save current Date and time before entering menu*/
  DateTime now = RTC.now();
  setHour = now.hour();
  setMin = now.minute();
  setDay = now.day();
  setMonth = now.month();
  setYear = now.year();

  Serial.print(now.hour(), DEC); Serial.print(":");
  Serial.print(now.minute(), DEC); Serial.print("--");
  Serial.print(now.day(), DEC);Serial.print("-");
  Serial.print(monthName[(int)now.month()-1]);Serial.print("-");
  Serial.println(now.year(), DEC);Serial.print("------");
  delay(100);
 
}

void showHour() {
  Serial.println("whoing hour");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("button up  detected");
    if (setHour == 23) {
      setHour = 0;
    } else {
      setHour ++;
    }
  }
  if (downButton.getSingleDebouncedRelease()) {
    Serial.println("button  down detected");
    if (setHour == 0) {
      setHour = 23;
    } else {
      setHour --;
    }

  }

  Serial.println(setHour, DEC);
  delay(50);

}

void showMin() {
  Serial.println("showing min");
  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("buttonup  detected");
    if (setMin == 259) {
      setMin = 0;
    } else {
      setMin ++;
    }
  }

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("button down detected");
    if (setMin == 0) {
      setMin = 59;
    } else {
      setMin --;
    }

  }
  Serial.println(setMin, DEC);
  delay(50);
}

void showDay(){
  Serial.println("show Day");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("button  up detected");
    if (setDay == 31) {
      setDay = 0;
    } else {
      setDay ++;
    }
  }

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("button down detected");
    if (setDay == 0) {
      setDay = 31;
    } else {
      setDay --;
    }  
}
Serial.println(setDay);
  delay(50);
}

void showMonth(){
  Serial.println("show Month");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("button  up detected");
    if (setMonth == 12) {
      setMonth = 0;
    } else {
      setMonth ++;
    }}
  

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("button down detected");
    if (setMonth == 0) {
      setMonth = 12;
    } else {
      setMonth --;
    }  
}
Serial.println(setMonth);
  delay(50);
}

void showYear(){
  Serial.println("show Year");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("button  up detected");
    if (setYear == 2020) {
      setYear = 0;
    } else {
      setYear ++;
    }}
  

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("button down detected");
    if (setYear == 0) {
      setYear = 2020;
    } else {
      setYear --;
    }  
}
Serial.println(setYear);
  delay(50);
}


