void setup() {

  Serial.begin(9600);
  Wire.begin();


  // set pinMode
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOSFET_PIN,OUTPUT);

  RTC.begin(); // initialize real time clock module
  if (! RTC.isrunning()) { // check if the RTC modulke is running
    Serial.println("RTC is NOT running ");
    RTC.adjust(DateTime(__DATE__, __TIME__)); // set date and time at compile time
  }

  lcd.begin();
  // assign each segments a write number
  lcd.createChar(1, bar1);
  lcd.createChar(2, bar2);
  lcd.createChar(3, bar2);
  lcd.createChar(4, bar4);
  lcd.createChar(5, bar5);
  lcd.createChar(6, bar6);
  lcd.createChar(7, bar7);
  lcd.createChar(8, bar8);

  lcd.createChar(9,bell);
  lcd.createChar(10,option);

  // set default
  int mainMenu  = 0;
  int menu = 0; // initialize at home page
  noTone(BUZZER_PIN);
  digitalWrite(MOSFET_PIN,LOW);
  
}// end setup()

