#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    int rD_s;
    int rA_s;
    float Celsius_s;
    float Fahrenheit_s;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Digital: ");
  Serial.println(myData.rD_s);
  Serial.print("Analog: ");
  Serial.println(myData.rA_s);
  Serial.print("C: ");
  Serial.println(myData.Celsius_s);
  Serial.print("F: ");
  Serial.println(myData.Fahrenheit_s);
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32(Receiver) MAC Address: ");
  Serial.println(WiFi.macAddress());
  
  //WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Init ESP-NOW
  // Once ESPNow is successfully Init, we will register for recv to get recv packer info
}
