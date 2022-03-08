//ESP-NOW SENDER ESP32 MAC: 24:6F:28:2B:66:74
//RECEIVER MAC ADDRESS: 7C:9E:BD:47:88:9C

#include <esp_now.h>
#include <WiFi.h>

//#define distval 34
esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x47, 0x88, 0x9C};
//uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x2B, 0x66, 0x74};

const int trigPin = 25;
const int echoPin = 33;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
//#define CM_TO_INCH 0.393701

int duration;
int distanceCm;
int distval;
//float distanceInch;

struct struct_data {
  int distval;
};

struct_data myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nPacket Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Successful" : "Delivery Failed");
 }

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  WiFi.mode(WIFI_STA);
  Serial.println("ESP32(Transmitter) MAC ADDRESS: ");
  Serial.println(WiFi.macAddress());

   if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
    }

    //After successful init, register for send CB to get transmitted packet status
    esp_now_register_send_cb(OnDataSent);

    //Register peer
    //esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    //Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer.");
      return;
      }
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  //distanceInch = distanceCm * CM_TO_INCH;

  //Send Values
  myData.distval = distanceCm;
  //myData.distval = 10;
  
  // Prints the distance in the Serial Monitor
  Serial.println();
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  /*
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  */

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success.");
    }
  else {
    Serial.println("Error sending the data.");
    }
  delay(1000);
}
