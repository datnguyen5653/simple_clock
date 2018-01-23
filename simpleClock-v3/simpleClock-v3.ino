
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
*/

/*Include library*/
#include<Wire.h>
#include<RTClib.h>
#include<dht.h>
#include<Pushbutton.h>
#include<EEPROM.h>


/*Initiallize object*/
Pushbutton upButton(4);
Pushbutton downButton(2);
Pushbutton menuButton(3);
Pushbutton mainButton(5);
RTC_DS1307 RTC;
dht DHT;

#define DHT11_PIN 11
#define BUZZER_PIN 9

/* global Variable */
int menu = 0;
int mainMenu = 0; //  main
int setHour, setMin, setDay, setMonth, setYear;
int setAlarmHour, setAlarmMin ;
String monthName[12] = {"Jan", "Feb", "Mar", "April", "May", "Jun", "Jul", "April",
                        "Sept", "Oct", "Nov", "Dec"
                       };
void setup() {

  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  pinMode(BUZZER_PIN, OUTPUT);

  if (! RTC.isrunning()) { // check if the RTC modulke is running
    Serial.println("RTC is NOT running ");
    RTC.adjust(DateTime(__DATE__, __TIME__)); // set date and time at compile time
  }
  int mainMenu  = 0;
  int menu = 0; // initialize at home page
  noTone(BUZZER_PIN);
}// end setup()






void loop() {

  // check time 
  // to trigger buzzer
  // Activate buzzer if clock reach alarm 
  if(setHour == EEPROM.read(0) && setMin == EEPROM.read(1)){
    tone(BUZZER_PIN,400,20000);
  }else{noTone(BUZZER_PIN);}
  

  // detect mainMenu button Push
  if (mainButton.getSingleDebouncedPress()) {
    mainMenu += 1;
    Serial.println("Main menu 1");
  }
  delay(30);

  // entering mainMenu button interface.
  // default main menu option
  if (mainMenu == 0) {
    showDateTime();
  }

  // first main menu option // change clock time
  if (mainMenu == 1) {
    changeClockMenu();

  }

  // seconf main menu option
  // change alarm time
  if (mainMenu == 2) {
    showAlarmClock();

    // detect mainMenu button again. to enter another menu
    if (menuButton.getSingleDebouncedPress()) {
      menu = menu + 1 ;
      Serial.println("menu add 1");
    }
    delay(50);

    // level2Menu - option 1
    if (menu == 1) {
      showAlarmClock();
      changeAlarmHour();

    }

    // level 2 menu - option 2
    if (menu == 2) {
      showAlarmClock();
      changeAlarmMin();

    }

    // level 3 menu - option 3
    if (menu == 3) {
      menu = 0 ;
      mainMenu = 0;

    }

  }

  // level 1 menu - last option .  return to default when reach limit.
  if (mainMenu == 3) {
    mainMenu = 0;
  }

  delay(50);
 

}// end loop()


/*
 * changeClockTime () 
 * level 1 menu - option 1 
 * change and adjust clock time .
 * 
 */

 void changeClockMenu() {
  if (menuButton.getSingleDebouncedPress()) {
    menu = menu + 1 ;
    Serial.println("menu add 1");
  }
  delay(50);


  if (menu == 0) {
    Serial.println("menu 0");
    showDateTime();
  }
  if (menu == 1) {
    Serial.println("menu 1");
    showDateTime();
    showHour();
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
  }
  if (menu == 2) {
    Serial.println("menu 2");
    showDateTime();
    showMin();
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
  }
  /* Date Setting*/
  if (menu == 3) {
    Serial.println("menu 3");
    showDateTime();
    showDay();
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
  } if (menu == 4) {
    Serial.println("menu 4");
    showDateTime();
    showMonth();
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
  }  if (menu == 5) {
    Serial.println("menu 5");
    showDateTime();
    showYear();
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
  }

  if (menu == 6) {
    Serial.println("menu 6");
    RTC.adjust(DateTime(setYear, setMonth, setDay, setHour, setMin, 0));
    //DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
    delay(300);
    menu = 0;
    mainMenu = 0;
  }
}

/*
 * these function show and adjust clock time and alarm time.
 * 
 * 
 */

 

void showAlarmClock() {
  Serial.print("Alarm Clock: "); Serial.print(EEPROM.read(0)); Serial.print(":");
  Serial.println(EEPROM.read(1));
}

void changeAlarmHour() {
  Serial.println("                            change Alarm Hour");
  setAlarmHour = EEPROM.read(0);   // fetch data from EEPROM
 // setAlarmMin = EEPROM.read(1);

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                  button up  detected");
    if (setAlarmHour == 23) {
      setAlarmHour = 0;
    } else {
      setAlarmHour ++;
    }
  }
  if (downButton.getSingleDebouncedRelease()) {
    Serial.println("                        button  down detected");
    if (setAlarmHour == 0) {
      setAlarmHour = 23;
    } else {
      setAlarmHour --;
    }

  }

  Serial.println(setAlarmHour, DEC);
   EEPROM.write(0, 0);
  EEPROM.write(0, setAlarmHour);
  delay(50);

}

void changeAlarmMin() {
  Serial.println("                            change Alarm Min");
 // setAlarmHour = EEPROM.read(0);   // fetch data from EEPROM
  setAlarmMin = EEPROM.read(1);

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                  button up  detected");
    if (setAlarmMin == 23) {
      setAlarmMin = 0;
    } else {
      setAlarmMin ++;
    }
  }
  if (downButton.getSingleDebouncedRelease()) {
    Serial.println("                        button  down detected");
    if (setAlarmMin == 0) {
      setAlarmMin = 59;
    } else {
      setAlarmMin --;
    }

  }

  Serial.println(setAlarmMin, DEC);
  EEPROM.write(1, 0);
  EEPROM.write(1, setAlarmMin);
  delay(50);

}




void showDateTime() {
  Serial.println("showing time");

  /*Save current Date and time before entering menu*/
  DateTime now = RTC.now();
  setHour = now.hour();
  setMin = now.minute();
  setDay = now.day();
  setMonth = now.month();
  setYear = now.year();
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(now.hour(), DEC); Serial.print(":");
  Serial.print(now.minute(), DEC); Serial.print("--");
  Serial.print(now.day(), DEC); Serial.print("-");
  Serial.print(monthName[(int)now.month() - 1]); Serial.print("-");
  Serial.print(now.year(), DEC); Serial.print("------");
  Serial.print(DHT.humidity);
  Serial.print(",\t");
  Serial.println(DHT.temperature);
  delay(100);

}

void showHour() {
  Serial.println("                             whoing hour");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                  button up  detected");
    if (setHour == 23) {
      setHour = 0;
    } else {
      setHour ++;
    }
  }
  if (downButton.getSingleDebouncedRelease()) {
    Serial.println("                        button  down detected");
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
  Serial.println( "                              howing min");
  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                        buttonup  detected");
    if (setMin == 259) {
      setMin = 0;
    } else {
      setMin ++;
    }
  }

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("                            button down detected");
    if (setMin == 0) {
      setMin = 59;
    } else {
      setMin --;
    }

  }
  Serial.println(setMin, DEC);
  delay(50);
}

void showDay() {
  Serial.println("                        show Day");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                                    button  up detected");
    if (setDay == 31) {
      setDay = 0;
    } else {
      setDay ++;
    }
  }

  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("                            button down detected");
    if (setDay == 0) {
      setDay = 31;
    } else {
      setDay --;
    }
  }
  Serial.println(setDay);
  delay(50);
}

void showMonth() {
  Serial.println("                              show Month");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                            button  up detected");
    if (setMonth == 12) {
      setMonth = 0;
    } else {
      setMonth ++;
    }
  }


  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("                              button down detected");
    if (setMonth == 0) {
      setMonth = 12;
    } else {
      setMonth --;
    }
  }
  Serial.println(setMonth);
  delay(50);
}

void showYear() {
  Serial.println("                              show Year");

  if (upButton.getSingleDebouncedRelease()) {
    Serial.println("                                button  up detected");
    if (setYear == 2020) {
      setYear = 0;
    } else {
      setYear ++;
    }
  }


  if (downButton.getSingleDebouncedRelease() ) {
    Serial.println("                    button down detected");
    if (setYear == 0) {
      setYear = 2020;
    } else {
      setYear --;
    }
  }
  Serial.println(setYear);
  delay(50);
}

void saveClock() {

}







