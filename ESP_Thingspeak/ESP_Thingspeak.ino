#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "Galaxy A01 Core9067";
const char* password = "samsung01";

// ThingSpeak channel details
unsigned long channelId = 2068681;
const char* apiKey = "ZMCWN4CE6S18BNSP";

// Initialize WiFi client and ThingSpeak client
WiFiClient client;

String receivedValue;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Con nected to WiFi!");

  // Initialize ThingSpeak client
  ThingSpeak.begin(client);
}

void loop() { // run over and over
  if (Serial.available()) {
      receivedValue = Serial.readStringUntil('%');

      Serial.println(receivedValue);

      int soil1Index = receivedValue.indexOf(',');
      String soil1 = receivedValue.substring(0, soil1Index);

      String removeSoil1 = removeWord(receivedValue, soil1);
      String removeFirstCharacter = removeSoil1.substring(1);
      int soil2Index = removeFirstCharacter.indexOf(',');
      String soil2 = removeFirstCharacter.substring(0, soil2Index);
      
      String removeSoil2 = removeWord(removeFirstCharacter, soil2);
      String removeFirstCharacter1 = removeSoil2.substring(1);
      int soil3Index = removeFirstCharacter1.indexOf(',');
      String soil3 = removeFirstCharacter1.substring(0, soil3Index);

      String removeSoil3 = removeWord(removeFirstCharacter1, soil3);
      String removeFirstCharacter2 = removeSoil3.substring(1);
      int ldrIndex = removeFirstCharacter2.indexOf(',');
      String ldr = removeFirstCharacter2.substring(0, ldrIndex);
      
      String removeLdr = removeWord(removeFirstCharacter2, ldr);
      String removeFirstCharacter3 = removeLdr.substring(1);
      int humidityIndex = removeFirstCharacter3.indexOf(',');
      String humidity = removeFirstCharacter3.substring(0, humidityIndex);

      String removeHumidity = removeWord(removeFirstCharacter3, humidity);
      String temperature = removeHumidity.substring(1);
      
      Serial.println(soil1);
      Serial.println(soil2);
      Serial.println(soil3);
      Serial.println(ldr);
      Serial.println(humidity);
      Serial.println(temperature);


       // set the fields with the values
      ThingSpeak.setField(1, soil1);
      ThingSpeak.setField(2, soil2);
      ThingSpeak.setField(3, soil3);
      ThingSpeak.setField(4, ldr);
      ThingSpeak.setField(5, humidity);
      ThingSpeak.setField(6, temperature);
      
      // write to the ThingSpeak channel
      int response = ThingSpeak.writeFields(channelId, apiKey);
  
      if(response == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(response));
      }

     delay(15000);
     Serial1.println("1");

      // Wait 15 seconds before sending the next set of values
  }
 
}


String removeWord(String str, String word) {
  int index = str.indexOf(word);
  if (index == -1) return str;
  int len = word.length();
  return str.substring(0, index) + str.substring(index+len);
}
