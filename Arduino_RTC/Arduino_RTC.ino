#include <SoftwareSerial.h> 
#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 rtc;

SoftwareSerial arduinoMain(3, 4);

const int buttonUpdate = 5;
int buttonStateUpdate = 0;

String updateValue;

int arraySchedules[3] = {6, 12, 18};

bool serialRecieved = false;

void setup()
{
    Serial.begin(9600);
    arduinoMain.begin(9600);
    
    pinMode(buttonUpdate, INPUT);
    
    if (! rtc.begin()) {
      Serial.flush();
      while (1);
    }
    
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.hour(), now.minute(), now.second(), 0, 0, 0));       
}
    
void loop()
{  
    DateTime now = rtc.now();
  
    if (Serial.available() > 0) {
        serialRecieved = true;
        
        updateValue = Serial.readStringUntil('%'); 
        
        int hourIndex = updateValue.indexOf(':');
        String hour = updateValue.substring(0, hourIndex);
        int hourInt = hour.toInt();
      
        String hourRemove = removeWord(updateValue, hour);
        String minute = hourRemove.substring(1);
        int minuteInt = hour.toInt();

        Serial.println("Hour : " + hour);
        Serial.println("Minute : " + minute);
        Serial.println("");
        Serial.println("");
          
        if(hourSetInt != 0 && minuteInt != 0){
          rtc.adjust(DateTime(now.hour(), now.minute(), now.second(), hourSetInt, minuteInt, 2));
          DateTime now = rtc.now();
        }
    }
    
    int hourNow = now.hour();
    int minutesNow = now.minute();
    int secondsNow = now.second();

    int hourIncrement = 6;
    
    Serial.println("Hour : " + hourNow);
    Serial.println("Minute : " + minutesNow);
    Serial.println("Seconds : " + secondsNow );
    Serial.println("");
    Serial.println("");

    if(serialRecieved == false){
        if(hourNow == 6 && minutesNow <= 3){
            arduinoMain.print("1%");
        }

        if(hourNow == 12 && minutesNow <= 3){
            arduinoMain.print("1%");
        }

        if(hourNow == 18 && minutesNow <= 3){
            arduinoMain.print("1%");
        }
    }
}


String removeWord(String str, String word) {
  int index = str.indexOf(word);
  if (index == -1) return str;
  int len = word.length();
  return str.substring(0, index) + str.substring(index+len);
}
