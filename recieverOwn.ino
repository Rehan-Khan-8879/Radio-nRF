#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL;
char receivedData;

void setup() {
  pinMode(5, OUTPUT);  // LED pin
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.begin(9600);
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    Serial.print("Received: ");
    Serial.println(receivedData);

    if (receivedData == 'A') {
      digitalWrite(5, HIGH);  // Turn LED ON
    } else if (receivedData == 'B') {
      digitalWrite(4, HIGH);  // Turn LED OFF
    } else if(receivedData == 'C'){
      digitalWrite(3,HIGH);
    } else if(receivedData == 'X'){
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
    }
  }
}