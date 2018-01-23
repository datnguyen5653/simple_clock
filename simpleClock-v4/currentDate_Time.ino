/*
 * This function excute and retrieve date and time data directly from the RTC module
 */
void getCurrentDateTime(){

  //debug
  Serial.println("getCurrentDateTime-");

  // initialize RTC module
  DateTime now= RTC.now();
  
  currentHour = now.hour();
  currentMin = now.minute();
  currentSec = now.second();
  currentDay = now.day();
  currentMonth = now.month();
  currentYear = now.year();
  
}

