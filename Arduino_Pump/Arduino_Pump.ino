#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);
SoftwareSerial arduinoSerial(9, 10);

int sensorPin = A3;

const int AirValue1 = 620;   //you need to replace this value with Value_1
const int WaterValue1 = 310;  //you need to replace this value with Value_2
int soilMoistureValue1 = 0;
int soilmoisturepercent1 = 0;

const int AirValue2 = 620;   //you need to replace this value with Value_1
const int WaterValue2 = 310;  //you need to replace this value with Value_2
int soilMoistureValue2 = 0;
int soilmoisturepercent2 = 0;

const int AirValue3 = 620;   //you need to replace this value with Value_1
const int WaterValue3 = 310;  //you need to replace this value with Value_2
int soilMoistureValue3 = 0;
int soilmoisturepercent3 = 0;

int mainPumpRelay = 6;
int RelayPin1 = 3;
int RelayPin2 = 4;
int RelayPin3 = 5;

int triggerValue1 = 60;
int triggerValue2 = 60;
int triggerValue3 = 60;

String receivedValue;

bool pumpSched1 = false;

const int buttonUpdate = 8;
int buttonStateUpdate = 0;

int loopCounter = 0;

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  espSerial.begin(115200);
  arduinoSerial.begin(9600);

  pinMode(mainPumpRelay, OUTPUT);
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);

  digitalWrite(mainPumpRelay, HIGH);
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);

  pinMode(buttonUpdate, INPUT);
}
void loop() {
  buttonStateUpdate = digitalRead(buttonUpdate); // for manual

  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);


  soilMoistureValue1 = analogRead(A0);  //put Sensor insert into soil
  soilmoisturepercent1 = map(soilMoistureValue1, AirValue1, WaterValue1, 0, 100);

  soilMoistureValue2 = analogRead(A1);  //put Sensor insert into soil
  soilmoisturepercent2 = map(soilMoistureValue2, AirValue2, WaterValue2, 0, 100);

  soilMoistureValue3 = analogRead(A2);  //put Sensor insert into soil
  soilmoisturepercent3 = map(soilMoistureValue3, AirValue3, WaterValue3, 0, 100);

  Serial.println(soilmoisturepercent1);
  Serial.println(soilmoisturepercent2);
  Serial.println(soilmoisturepercent3);


  if(loopCounter >= 60){

      loopCounter = 0;
      boolean moisture1Trigger1 = false;
      boolean moisture2Trigger2 = false;
      boolean moisture3Trigger3 = false;

      
      //soil Moisture 1
      if(soilmoisturepercent1 >= 100){
          Serial.println("Soil Moisture 1: 100%");
          Serial.println("Relay 1: ON%");

          moisture1Trigger1 = true;
                    
          digitalWrite(RelayPin1, LOW);
      }
                
      else if(soilmoisturepercent1 <=0){
          Serial.println("Soil Moisture 1: 0%");
          Serial.println("Relay 1: OFF%");

          moisture1Trigger1 = false;
                    
          digitalWrite(RelayPin1, HIGH);
      }
                
      else if(soilmoisturepercent1 > 0 && soilmoisturepercent1 < 100){
           Serial.println("Soil Moisture 1: " + String(soilmoisturepercent1) + "%");
                    
           if(soilmoisturepercent1 < triggerValue1){
                 Serial.println("Relay 1: ON%");

                 moisture1Trigger1 = true;
                      
                 digitalWrite(RelayPin1, LOW);
           }
                
           else if(soilmoisturepercent1 >=  triggerValue1){
                 Serial.println("Relay 1: OFF%");

                 moisture1Trigger1 = false;
                      
                 digitalWrite(RelayPin1, HIGH);
           }
      }
      //****************

                

     Serial.println(" ");
     Serial.println(" ");
     Serial.println(" ");


              

     //soil Moisture 2
     if(soilmoisturepercent2 >= 100){
            Serial.println("Soil Moisture 2: 100%");
            Serial.println("Relay 2: ON%");

            moisture2Trigger2 = true;
                    
            digitalWrite(RelayPin2, LOW);
     }
                
     else if(soilmoisturepercent2 <=0){
            Serial.println("Soil Moisture 2: 0%");
            Serial.println("Relay 2: OFF%");

            moisture2Trigger2 = false;
                    
            digitalWrite(RelayPin2, HIGH);
     }
                
     else if(soilmoisturepercent2 > 0 && soilmoisturepercent2 < 100){
            Serial.println("Soil Moisture 2: " + String(soilmoisturepercent2) + "%");

            if(soilmoisturepercent2 < triggerValue2){
                  Serial.println("Relay 2: ON%");

                  moisture2Trigger2 = true;
                      
                  digitalWrite(RelayPin2, LOW);
            }
                
            else if(soilmoisturepercent2 >=  triggerValue2){
                  Serial.println("Relay 2: OFF%");

                  moisture2Trigger2 = false;
                      
                  digitalWrite(RelayPin2, HIGH);
            }
     }
     //****************

                

     Serial.println(" ");
     Serial.println(" ");
     Serial.println(" ");


                

     //soil Moisture 3
     if(soilmoisturepercent3 >= 100){
          Serial.println("Soil Moisture 3: 100%");
          Serial.println("Relay 3: ON%");

          moisture3Trigger3 = true;
                    
          digitalWrite(RelayPin3, LOW);
      }
                
      else if(soilmoisturepercent3 <=0){
          Serial.println("Soil Moisture 3: 0%");
          Serial.println("Relay 3: OFF%");

          moisture3Trigger3 = false;
                    
          digitalWrite(RelayPin3, HIGH);
      }
                
      else if(soilmoisturepercent3 > 0 && soilmoisturepercent3 < 100){
          Serial.println("Soil Moisture 3: " + String(soilmoisturepercent3) + "%");
                    
          if(soilmoisturepercent3 < triggerValue3){
                Serial.println("Relay 3: ON%");

                moisture3Trigger3 = true;
                      
                digitalWrite(RelayPin3, LOW);
          }
                
          else if(soilmoisturepercent3 >=  triggerValue3){
                Serial.println("Relay 3: OFF%");

                moisture3Trigger3 = false;
                      
                digitalWrite(RelayPin3, HIGH);
          }
      }
      //****************

      if(moisture1Trigger1 == true || moisture2Trigger2 == true || moisture3Trigger3 == true){
          digitalWrite(mainPumpRelay, LOW);
          Serial.println("Activating Pump");

          if(moisture1Trigger1 == true){
              digitalWrite(RelayPin1, LOW);
          }

          if(moisture2Trigger2 == true){
              digitalWrite(RelayPin2, LOW);
          }

          if(moisture3Trigger3 == true){
              digitalWrite(RelayPin3, LOW);
          }
      }

      delay(10000);
      
      digitalWrite(RelayPin1, HIGH);
      digitalWrite(RelayPin2, HIGH);
      digitalWrite(RelayPin3, HIGH);
  }

                

  //if button is click update data
  if(buttonStateUpdate == HIGH) {
        espSerial.println("1");
  }
  

  
  if (Serial.available() > 0) {
      receivedValue = Serial.readStringUntil('%');
      
      Serial.println("Recieved: " + receivedValue);

      
        //if ang recieved value is hindi sya equals sa 1
        if(receivedValue != "1" && receivedValue != "0"){
            Serial.println("Update Recieved");
            Serial.println("");
            
            int moisture1Index = receivedValue.indexOf(',');
            String moisture1 = receivedValue.substring(0, moisture1Index);
            int moisture1Int = moisture1.toInt();
    
            String moisture1Remove = removeWord(receivedValue, moisture1);
            String removeComa1 = moisture1Remove.substring(1);
            int moisture2Index = removeComa1.indexOf(',');
            String moisture2 = removeComa1.substring(0, moisture2Index);
            int moisture2Int = moisture2.toInt();
    
            String moisture2Remove = removeWord(removeComa1, moisture2);
            String moisture3 = moisture2Remove.substring(1);
            int moisture3Int = moisture3.toInt();
    
            if(moisture1Int != 0){
                triggerValue1 = moisture1Int;
            }
    
            if(moisture2Int != 0){
                triggerValue2 = moisture2Int;
            }
    
            if(moisture3Int != 0){
                triggerValue3 = moisture3Int;
            }

            Serial.println("Trigger Value 1: " + triggerValue1);
            Serial.println("Trigger Value 2: " + triggerValue2);
            Serial.println("Trigger Value 3: " + triggerValue3);
            
            Serial.println("");
            Serial.println("");
            Serial.println("");

        }

      
        else if(receivedValue == "1"){
               
            if(pumpSched1 == false){
              
                pumpSched1 = true;


                Serial.println("Main Pump is Turned On");
                digitalWrite(mainPumpRelay, LOW);


                //soil Moisture 1
                if(soilmoisturepercent1 >= 100){
                    Serial.println("Soil Moisture 1: 100%");
                    Serial.println("Relay 1: ON%");
                    
                    digitalWrite(RelayPin1, LOW);
                }
                
                else if(soilmoisturepercent1 <=0){
                    Serial.println("Soil Moisture 1: 0%");
                    Serial.println("Relay 1: OFF%");
                    
                    digitalWrite(RelayPin1, HIGH);
                }
                
                else if(soilmoisturepercent1 > 0 && soilmoisturepercent1 < 100){
                    Serial.println("Soil Moisture 1: " + String(soilmoisturepercent1) + "%");
                    
                    if(soilmoisturepercent1 < triggerValue1){
                      Serial.println("Relay 1: ON%");
                      
                      digitalWrite(RelayPin1, LOW);
                    }
                
                    else if(soilmoisturepercent1 >=  triggerValue1){
                      Serial.println("Relay 1: OFF%");
                      
                      digitalWrite(RelayPin1, HIGH);
                    }
                }
                //****************

                

              Serial.println(" ");
              Serial.println(" ");
              Serial.println(" ");


              

              //soil Moisture 2
                if(soilmoisturepercent2 >= 100){
                    Serial.println("Soil Moisture 2: 100%");
                    Serial.println("Relay 2: ON%");
                    
                    digitalWrite(RelayPin2, LOW);
                }
                
                else if(soilmoisturepercent2 <=0){
                    Serial.println("Soil Moisture 2: 0%");
                    Serial.println("Relay 2: OFF%");
                    
                    digitalWrite(RelayPin2, HIGH);
                }
                
                else if(soilmoisturepercent2 > 0 && soilmoisturepercent2 < 100){
                    Serial.println("Soil Moisture 2: " + String(soilmoisturepercent2) + "%");

                    if(soilmoisturepercent2 < triggerValue2){
                      Serial.println("Relay 2: ON%");
                      
                      digitalWrite(RelayPin2, LOW);
                    }
                
                    else if(soilmoisturepercent2 >=  triggerValue2){
                      Serial.println("Relay 2: OFF%");
                      
                      digitalWrite(RelayPin2, HIGH);
                    }
                }
                //****************

                

                Serial.println(" ");
                Serial.println(" ");
                Serial.println(" ");


                

                //soil Moisture 3
                if(soilmoisturepercent3 >= 100){
                    Serial.println("Soil Moisture 3: 100%");
                    Serial.println("Relay 3: ON%");
                    
                    digitalWrite(RelayPin3, LOW);
                }
                
                else if(soilmoisturepercent3 <=0){
                    Serial.println("Soil Moisture 3: 0%");
                    Serial.println("Relay 3: OFF%");
                    
                    digitalWrite(RelayPin3, HIGH);
                }
                
                else if(soilmoisturepercent3 > 0 && soilmoisturepercent3 < 100){
                    Serial.println("Soil Moisture 3: " + String(soilmoisturepercent3) + "%");
                    
                    if(soilmoisturepercent3 < triggerValue3){
                      Serial.println("Relay 3: ON%");
                      
                      digitalWrite(RelayPin3, LOW);
                    }
                
                    else if(soilmoisturepercent3 >=  triggerValue3){
                      Serial.println("Relay 3: OFF%");
                      
                      digitalWrite(RelayPin3, HIGH);
                    }
                }
                //****************
                

              delay(10000);  

              Serial.println(" ");
              Serial.println("All Relay is OFF");

              digitalWrite(RelayPin1, HIGH);
              digitalWrite(RelayPin2, HIGH);
              digitalWrite(RelayPin3, HIGH);


              Serial.println(" ");
              Serial.println(" ");
              Serial.println(" ");

            }
            
        }

        else if(receivedValue == "0"){
            Serial.println("PUMP OFF");
            pumpSched1 = false;
            Serial.println(" ");
            Serial.println(" ");
            Serial.println(" ");
        }
    }

    
    delay(5000);

    loopCounter = loopCounter + 5;
    
}

String removeWord(String str, String word) {
  int index = str.indexOf(word);
  if (index == -1) return str;
  int len = word.length();
  return str.substring(0, index) + str.substring(index+len);
}
