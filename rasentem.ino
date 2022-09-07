#include <WiFi.h>
#include <esp_now.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x24, 0x8A, 0xC0};
//typedef struct struct_message {
//  int rD_s;
//  int rA_s;
//  float Celsius_s;
//  float Fahrenheit_s;
//} struct_message;
//struct_message myData;

//void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//  Serial.print("\r\nLast Packet Send Status:\t");
//  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//}

#define ONE_WIRE_BUS 33
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;
const int rD = 25; //4;
const int rA = 26; //A0;

int rA_val;

void setup()
{
  Serial.begin(115200);
//  Serial.println("ESP32(Sender) MAC Address: ");
//  Serial.println(WiFi.macAddress());
  pinMode(rD, INPUT);
  pinMode(rA, INPUT);
  //pinMode(temp, INPUT);
  sensors.begin();

//  if (esp_now_init() != ESP_OK) {
//    Serial.println("Error initializing ESP-NOW");
//    return;
//  }
//  esp_now_register_send_cb(OnDataSent);
//  esp_now_peer_info_t peerInfo;
//  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//  peerInfo.channel = 0;  
//  peerInfo.encrypt = false;
//         
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
}

void loop()
{
    sensors.requestTemperatures();
//    myData.rD_s = digitalRead(rD);
//    myData.rA_s = analogRead(rA);
//    myData.Celsius_s = sensors.getTempCByIndex(0);
//    myData.Fahrenheit_s = sensors.getTempFByIndex(0);

//    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
//   
//    if (result == ESP_OK) {
//      Serial.println("Sent with success");
//    }
//    else {
//      Serial.println("Error sending the data");
//    }
    
    // RS
    if(digitalRead(rD) == LOW) 
      {
        Serial.println("Digital value : Wet"); 
      }
    else
      {
        Serial.println("Digital value : Dry"); 
      }
    rA_val = analogRead(rA); 
    Serial.print("Analog value : ");
    Serial.println(rA_val); 
    Serial.println("");

    // Temp
    //sensors.requestTemperatures();
    Serial.print("Celsius temperature: ");
    //You can have more than one IC on the same bus (wire).
    Serial.println(sensors.getTempCByIndex(0)); 
    Serial.print("Fahrenheit temperature: ");
    Serial.println(sensors.getTempFByIndex(0));
//    Celsius=sensors.getTempCByIndex(0);
//    Fahrenheit=sensors.toFahrenheit(Celsius);
//    Serial.print("C: ");
//    Serial.println(Celsius);
//    Serial.print("F: ");
//    Serial.println(Fahrenheit); 
    delay(1000);
}
