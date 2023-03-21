#include "DHT.h"
#define DHTPIN 8 // The same pin number mentioned above
#include <SoftwareSerial.h>

SoftwareSerial espSerial(9, 10);

DHT dht(DHTPIN, DHT11);

int PWMValue; //Sets PWMValue as integer

int loopCounter = 0;

const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;

const int AirValue1 = 620;   //you need to replace this value with Value_1
const int WaterValue1 = 310;  //you need to replace this value with Value_2
int soilMoistureValue1 = 0;
int soilmoisturepercent1=0;

const int AirValue2 = 620;   //you need to replace this value with Value_1
const int WaterValue2 = 310;  //you need to replace this value with Value_2
int soilMoistureValue2 = 0;
int soilmoisturepercent2=0;

String sensorValues;

int mainPumpRelay = 7;

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps

  espSerial.begin(115200);

  pinMode(mainPumpRelay, OUTPUT);

  digitalWrite(mainPumpRelay, HIGH);
  
  dht.begin();
}

void loop() {

  float h = dht.readHumidity(); //measure humidity
  float t = dht.readTemperature(); //measure temperature
  
  if (isnan(h) || isnan(t)) { //Check. If the reading fails, then "Read error" is displayed and the program exits
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C "); //Weep the readings on the screen

  if(t < 27){
      digitalWrite(mainPumpRelay, LOW);
  }

  else if(t > 27){
      digitalWrite(mainPumpRelay, HIGH);
  }

  int sensorValue = analogRead(A1); // read the value from the sensor


  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  soilMoistureValue1 = analogRead(A2);  //put Sensor insert into soil
  soilmoisturepercent1 = map(soilMoistureValue1, AirValue1, WaterValue1, 0, 100);

  soilMoistureValue2 = analogRead(A3);  //put Sensor insert into soil
  soilmoisturepercent2 = map(soilMoistureValue2, AirValue2, WaterValue2, 0, 100);

  //Soil 1
  if(soilmoisturepercent >= 100)
  {
    soilmoisturepercent = 100;
  }
  
  else if(soilmoisturepercent <=0)
  {
    soilmoisturepercent = 0;
  }
  
  else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
  {
    soilmoisturepercent = soilmoisturepercent;
  }
  //*******************


  //Soil 2
  if(soilmoisturepercent1 >= 100)
  {
    soilmoisturepercent1 = 100;
  }
  
  else if(soilmoisturepercent1 <=0)
  {
    soilmoisturepercent1 = 0;
  }
  
  else if(soilmoisturepercent1 >0 && soilmoisturepercent1 < 100)
  {
    soilmoisturepercent1 = soilmoisturepercent1;
  }
  //*******************



  //Soil 3
  if(soilmoisturepercent2 >= 100)
  {
    soilmoisturepercent2 = 100;
  }
  
  else if(soilmoisturepercent2 <=0)
  {
    soilmoisturepercent2 = 0;
  }
  
  else if(soilmoisturepercent2 >0 && soilmoisturepercent2 < 100)
  {
    soilmoisturepercent2 = soilmoisturepercent2;
  }
  //*******************
  

  sensorValues = String(String(soilmoisturepercent) + ","  + String(soilmoisturepercent1) + "," + String(soilmoisturepercent2) + "," + String(sensorValue) + "," + String(h) + "," + String(t) + "%");

  if(loopCounter >= 16){
      espSerial.println(sensorValues);
      loopCounter = 0;
  }

  loopCounter = loopCounter + 1;
  delay(1000);
}
