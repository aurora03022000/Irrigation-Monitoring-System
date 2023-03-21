#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

// Replace with your network credentials
const char *ssid     = "Galaxy A01 Core9067";
const char *password = "samsung01";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial1.begin(9600);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0

  timeClient.setTimeOffset(28800);
}

void loop() {
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  
  String formattedTime = timeClient.getFormattedTime();

  int currentHour = timeClient.getHours();
  int currentMinutes = timeClient.getMinutes();

//  if(currentHour == 6 && currentMinutes <= 2){
//      Serial1.print("1%");
//  }
//
//  if(currentHour == 18 && currentMinutes > 23 && currentMinutes < 25){
//      Serial1.print("1%");
//  }
//
//  else if(currentHour == 18 && currentMinutes >27   && currentMinutes < 29){
//      Serial1.print("1%");
//  }

  int scheduleTime = 5;
  boolean noSchedule = true;
  for(;;){
     if(scheduleTime >= 60){
        break;
     }
     
     else if(currentMinutes == scheduleTime){
        Serial1.print("1%");
        noSchedule = false;
        break;
     }

     else{
        scheduleTime = scheduleTime + 5;
        noSchedule = true;
     }
  }

  
  if(noSchedule == true){
      Serial1.print("0%");
  }

  delay(5000);  
}
