//ESP-NOW RECEIVER ESP32 MAC: 7C:9E:BD:47:88:9C
//Receiving from - 24:6F:28:2B:66:74
// Include Basic input and output pins
#include <esp_now.h>
#include <WiFi.h>

#define ledr 33
#define ledy 32
#define ledg 25
#define buzz 26

typedef struct struct_data {
  int distval;
};

struct_data myData;

int playing = 0;
void tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(pin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
  playing = pin; // store pin
}
void noTone() {
  tone(playing, 0);
}

//CB when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println();
  Serial.println("INCOMING DATA");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance Value: ");
  Serial.println(myData.distval);
  Serial.println();
  
  //code for leds
  if (myData.distval <= 15) {
    Serial.println("STOP NOW!");
    digitalWrite(ledr, LOW);
    digitalWrite(ledy, HIGH);
    digitalWrite(ledg, HIGH);
    tone(buzz, 1000); // Send KHz sound signal...
    delay(2000);        
    noTone();     // Stop sound
    delay(10);
    }
  if ((myData.distval > 15)&&(myData.distval <= 30)) {
    Serial.println("PREPARE TO STOP!");
    digitalWrite(ledy, LOW);
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, HIGH);
    digitalWrite(buzz, LOW);
    tone(buzz, 3000); // Send KHz sound signal...
    delay(400);        
    noTone();     // Stop sound
    delay(400);
    }
  if ((myData.distval > 30)&&(myData.distval <= 60)) {
    Serial.println("SLOW DOWN!");
    digitalWrite(ledy, LOW);
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, HIGH);
    digitalWrite(buzz, LOW);
    tone(buzz, 3000); // Send KHz sound signal...
    delay(1000);        
    noTone();     // Stop sound
    delay(1000);
    }
  if (myData.distval > 60) {
    Serial.println("KEEP GOING!");
    digitalWrite(ledg, LOW);
    digitalWrite(ledy, HIGH);
    digitalWrite(ledr, HIGH);
    digitalWrite(buzz, LOW);
    }
 }

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("ESP32(Receiver) MAC Address: ");
  Serial.println(WiFi.macAddress());

  pinMode(ledr, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(buzz, OUTPUT);

  digitalWrite(ledr, HIGH);
  digitalWrite(ledy, HIGH);
  digitalWrite(ledg, HIGH);
  digitalWrite(buzz, LOW);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW.");
    return;
   }
   //After init, register for recv CB to get received packet info
   esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // XD
  }
