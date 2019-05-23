#include <dht.h>
#include <LiquidCrystal.h>


dht DHT;

//declaring io pins
const int mSense1 = A1;
const int mSense2 = A2;
const int control = A0;
const int solenoid = 3;
const int tSense = 7;
#define DHT11_PIN 13


//declaring variables
int mSenseOut1;
int mSenseOut2;
float bias = 1.0;
int target = 50;
float senseAvg;
float temp;
float humidity;
float target2;

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

  int chk = DHT.read11(DHT11_PIN);
  temp = DHT.temperature;
  humidity = DHT.temperature;
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.print("\tHumidity:");
  Serial.println(humidity);
  
  temp = map(round(temp), 0, 50, 1400, 600);
  humidity = map(round(humidity), 0, 100, 1400, 600);
  temp = temp / 1000;
  humidity = humidity / 1000;

  bias = (humidity + temp) / 2;
  
  Serial.print("temp:");
  Serial.print(temp);
  Serial.print("\thumidity:");
  Serial.println(humidity);
  
  
  int temp1 = analogRead(mSense1);
  int temp2 = analogRead(mSense2);
  mSenseOut1 = map(temp1, 0, 1023, 0, 255);
  mSenseOut2 = map(temp2, 0, 1023, 0, 255);

  Serial.print("sensor1:");
  Serial.print(mSenseOut1);
  Serial.print("\tsensor2:");
  Serial.println(mSenseOut2);
  
  
  
  senseAvg = (mSenseOut1 + mSenseOut2) / 2;

  target2 = target * bias;

  Serial.println(bias);
  
  //outputs to lcd
  lcd.setCursor(0, 0);
  lcd.print("senseAvg:");
  lcd.setCursor(9, 0);
  lcd.print(round(senseAvg));
  lcd.setCursor(0, 1);
  lcd.print("target:");
  lcd.setCursor(7, 1);
  lcd.print(round(target2));

  //changing target soil moisture while running if needed
  int controlOut = analogRead(control);
  if (controlOut > 90 && controlOut < 110 && target < 150)
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
  if (senseAvg < target2 && senseAvg < 255)
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
