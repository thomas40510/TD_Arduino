#include <LiquidCrystal.h>

const byte pinBtn = 19;
const byte pinTemp = A4;

long t0;

float tempV;
float moyenne = 0.0;

float a = 0.1;

LiquidCrystal lcd(31,33,37,39,41,43);

void setup() {
  //init pins
  pinMode(pinBtn, INPUT);
  pinMode(pinTemp, INPUT);

  //init serial
  Serial.begin(19200);
  Serial.println("Ready to begin.");

  //lcd init
  lcd.begin(16,2);

  t0 = millis();

  lcd.clear();

  attachInterrupt(digitalPinToInterrupt(pinBtn), resetMoyenne, RISING);
}

void loop() {
  if (millis() - t0 >= 1800){
    t0 = millis();
    //read temp sensor voltage and calculate mean value
    tempV = analogRead(pinTemp);
    moyenne = a*tempV + (1-a) * moyenne;

    //display values on LCD
    lcd.setCursor(0,0);
    lcd.print("Val = " + String(tempV) + "mV");
    lcd.setCursor(0,1);
    lcd.print("Moy = " + String(moyenne) + "mV");
  }
}

void resetMoyenne(){
  /*
   * resets moyenne to current voltage value
   */
  moyenne = tempV;
}
