#include <LiquidCrystal.h>

//declaring io pins
const int mSense1 = A1;
const int mSense2 = A2;
const int control = A0;
const int solenoid = 3;

//declaring variables
int mSenseOut1 = 0;
int mSenseOut2 = 0;
float bias = 1.0;
int target = 50;
float senseAvg = 0;

//declaring lcd
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);

  //initialises lcd
  lcd.begin(16, 2);

  //turns off solenoid
  digitalWrite(solenoid, LOW);

  //runs set target routine
  setTarget();
}

void setTarget()
{
  bool unset = true;
  while (unset = true)
  {
    
    //IMPORTANT
    //the lcd sheild detects what button is down
    //by using an analog pin and a series of resistors
    
    
    //reads control pin(buttons on lcd
    int controlOut = analogRead(control);

    //if up button pressed
    if (controlOut > 90 && controlOut < 110 && target < 250)
    {
      //sets target int higher
      target += 10;
      Serial.println(target);
    }
    //if down button pressed
    if (controlOut > 245 && controlOut < 265 && target > 10)
    {
      //sets target int lower
      target -= 10;
      Serial.println(target);
    } 
    // if selcet button down
    if (controlOut > 630 && controlOut < 650)
    {
      //stop this function then proceed with void loop()
      unset = false;
      break;
    } 
    //outputs to lcd
    lcd.print("target:");
    lcd.setCursor(7, 0);
    lcd.print(round(target));
    delay(100);
    lcd.clear();
  }
}


void loop() {
  lcd.clear();

  int temp1 = analogRead(mSense1);
  int temp2 = analogRead(mSense2);
  mSenseOut1 = map(temp1, 0, 1023, 0, 255);
  mSenseOut2 = map(temp2, 0, 1023, 0, 255);

  Serial.print("sensor1 = ");
  Serial.print(mSenseOut1);
  Serial.print("\tsensor2 = ");
  Serial.println(mSenseOut2);
  
  senseAvg = (mSenseOut1 + mSenseOut2) / 2;

  //outputs to lcd
  lcd.setCursor(0, 0);
  lcd.print("senseAvg:");
  lcd.setCursor(9, 0);
  lcd.print(round(senseAvg));
  lcd.setCursor(0, 1);
  lcd.print("target:");
  lcd.setCursor(7, 1);
  lcd.print(round(target));

  //changing target soil moisture while running if needed
  int controlOut = analogRead(control);
  if (controlOut > 90 && controlOut < 110 && target < 250)
  {
    target += 10;
    Serial.println(target);
  }

  if (controlOut > 245 && controlOut < 265 && target > 10)
  {
    target -= 10;
    Serial.println(target);
  }

  //if both sensors average is below the target moisture then run water routine
  if (senseAvg < target * bias && senseAvg < 255)
  {
    water();
  }

  delay(1);
}

void water()
{
  //opens solenoid
  digitalWrite(solenoid, HIGH);
  Serial.println("solenoid is ON");
  delay(500);
  //closes solenoid
  digitalWrite(solenoid, LOW);
  Serial.println("solenoid is OFF");
  //waits for water to spread before resuming checking
  delay(1000);
}
