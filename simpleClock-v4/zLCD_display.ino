
/*
   printBigNumber function
   parameter: int value , int column.
*/
void printBigNum(int value, int col ) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }
}

/*
 * This funtion display time in big font at the home page
 */
void printTime(uint8_t _hour, uint8_t _min){
  byte hourFDigit, hourSDigit , minFDigit, minSDigit ; 

  // assign each digit into correct variable 
  hourFDigit = (_hour - (_hour%10))/10;
  hourSDigit = _hour%10 ; 
  minFDigit =  (_min - (_min%10))/10;
  minSDigit = _min%10;

  lcd.setCursor(0,0);// initialize cursor to 0 position

  printBigNum(hourFDigit,0);// print first hour digti
  printBigNum(hourSDigit,3);// print second hour digit
  printBigNum(minFDigit,6);// print first min digit
  printBigNum(minSDigit,9);// print second min digit
  
  
}

void display_optionChar(int row){
  lcd.setCursor(0,row);// set cursor to requested row
  lcd.write(10); //  10 == custom character option
}


