#include <LiquidCrystal.h>

const int mSense1 = A1;
const int mSense2 = A2;

const int control = A0;

const int solenoid = 3;

int mSenseOut1 = 0;
int mSenseOut2 = 0;

int thresh = 50;

float senseAvg = 0;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.print("starting");

  digitalWrite(solenoid, LOW);

  setThresh();
}

void setThresh()
{
  bool unset = true;
  while (unset = true)
  {
    int controlOut = analogRead(control);
    Serial.println(controlOut);
    if (controlOut > 90 && controlOut < 110 && thresh < 250)
    {
      thresh += 10;
      Serial.println(thresh);
    }
  
    if (controlOut > 245 && controlOut < 265 && thresh > 10)
    {
      thresh -= 10;
      Serial.println(thresh);
    } 
    if (controlOut > 630 && controlOut < 650)
    {
      unset = false;
      break;
    } 
    lcd.print("threshold:");
    lcd.setCursor(10, 0);
    lcd.print(round(thresh));
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

  lcd.setCursor(0, 0);
  lcd.print("senseAvg:");
  lcd.setCursor(9, 0);
  lcd.print(round(senseAvg));
  lcd.setCursor(0, 1);
  lcd.print("threshold:");
  lcd.setCursor(10, 1);
  lcd.print(round(thresh));

  int controlOut = analogRead(control);
  if (controlOut > 90 && controlOut < 110 && thresh < 250)
  {
    thresh += 10;
    Serial.println(thresh);
  }

  if (controlOut > 245 && controlOut < 265 && thresh > 10)
  {
    thresh -= 10;
    Serial.println(thresh);
  }

  if (senseAvg < thresh && senseAvg < 255)
  {
    water();
  }

  delay(1);
}

void water()
{
  digitalWrite(solenoid, HIGH);
  Serial.println("solenoid is ON");
  delay(500);
  digitalWrite(solenoid, LOW);
  Serial.println("solenoid is OFF");
  delay(1000);
}
