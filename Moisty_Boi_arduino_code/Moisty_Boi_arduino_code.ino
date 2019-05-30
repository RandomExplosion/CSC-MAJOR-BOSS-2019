
#include <dht.h>
#include <LiquidCrystal.h>

//Moisture Sensor Analog Pins
const int mSense1 = A1;
const int mSense2 = A2;

//?
const int control = A0;

//Digital pin connected to solenoid (through relay).
const int solenoid = 3;

//Pin attached to the temperature and Humidity Sensor
#define DHT11_PIN 13

//declaring variables
int mSenseOut1;
int mSenseOut2;

float bias = 1.0;

//Target readout from the moisture sensors
int target = 50;

float senseAvg; //Current average readout from the sensors *!*
float temp; //Temperature readout
float humidity; //Humidity
float target2; //*!*

//Declaring lcd screen controller with the following Pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Declaring HT (Humidity&temperature) sensor controller
dht DHT;

void setup() {

    //Open Serial Connection with computer
    Serial.begin(9600);

    //Initalise LCD Screen
    lcd.begin(16, 2);

    //Disable Solenoid relay
    digitalWrite(solenoid, LOW);

    //Run Set Target Routine
    setTarget();
}

void setTarget()
{
    bool unset = true;
    while (unset = true)
    {

        //IMPORTANT
        //the lcd shield detects what button is down
        //by using an analog pin and a series of resistors


        //reads control pin(buttons on lcd
        int controlOut = analogRead(control);

        //if up button pressed
        if (controlOut > 90 && controlOut < 110 && target < 250)
        {
            //Raise target int
            target += 10;
            Serial.println(target);
        }
        //if down button pressed
        if (controlOut > 245 && controlOut < 265 && target > 10)
        {
            //Lower target int
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

    //finding temperature and humidity
    int chk = DHT.read11(DHT11_PIN);
    temp = DHT.temperature;
    humidity = DHT.temperature;

    //setting and finding the bias
    temp = map(round(temp), 0, 50, 600, 1400);
    humidity = map(round(humidity), 0, 100, 1400, 600);
    temp = temp / 1000;
    humidity = humidity / 1000;
    bias = (humidity + temp) / 2; 

    //setting sensor output
    int temp1 = analogRead(mSense1);
    int temp2 = analogRead(mSense2);
    mSenseOut1 = map(temp1, 0, 1023, 0, 255);
    mSenseOut2 = map(temp2, 0, 1023, 0, 255); 
    senseAvg = (mSenseOut1 + mSenseOut2) / 2;

    //setting target with bias
    target2 = target * bias;
    Serial.println(bias);

    //Print Info to the LCD screen
    lcd.setCursor(0, 0);
    lcd.print("SensorAvg: ");
    lcd.setCursor(9, 0);
    lcd.print(round(senseAvg));
    lcd.setCursor(0, 1);
    lcd.print("Target: ");
    lcd.setCursor(7, 1);
    lcd.print(round(target2));

    int controlOut;
    //changing target soil moisture while running if needed
    if (controlOut != analogRead(control);)
    {
        controlOut = analogRead(control);
    }

    if (controlOut > 90 && controlOut < 110 && target < 150)
    {
        target += 10;
        Serial.println(target); //Couldn't make sense of this *!* (don't know what button this refers to)
    }

    if (controlOut > 245 && controlOut < 265 && target > 10)
    {
        target -= 10;
        Serial.println(target); //Couldn't make sense of this *!* (don't know what button this refers to)
    }

    //If both sensors average is below the target moisture then run water routine.
    if (senseAvg < target2 && senseAvg < 255)
    {
        water();
    }
    if (senseAvg > target2)
    {
        delay(1000);
    }
    else
    {
        delay(1);
    }

}

void water()
{
    digitalWrite(solenoid, HIGH); //Turn On Solenid
    Serial.println("Solenoid is ON"); //Log to the serial port
    delay(500); //Wait
    digitalWrite(solenoid, LOW); //Close the solenoid
    Serial.println("Solenoid is OFF"); //Log to the serial port
    delay(2000); //Wait for the water to spread through the soil before resuming
}
