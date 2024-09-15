#include <SPI.h>
#include <RF24.h>

#define but1 2
#define but2 3
#define but3 4


int val1;
int val2;
int val3;


RF24 radio(7, 8);  // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL;
char dataToSend = 'A';  // Initial data

void setup() {
  radio.begin();
  pinMode(but1,INPUT_PULLUP);
  pinMode(but2,INPUT_PULLUP);
  pinMode(but3,INPUT_PULLUP);

  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_LOW);
  Serial.begin(9600);
}

void loop() {
  radio.write(&dataToSend, sizeof(dataToSend));  // Send char data
  Serial.print("Sent: ");

  Serial.print(val1);
  Serial.print("  ");
  Serial.print(val2);
  Serial.print("  ");
  Serial.println(val3);
   val1 = digitalRead(but1);
   val2 = digitalRead(but2);
   val3 = digitalRead(but3);
   if(val1 == 0){
    dataToSend = 'A' ;
   }else if(val2 == 0){
    dataToSend = 'B' ;
   }else if(val3 == 0){
    dataToSend = 'C';
   }
   else{
    dataToSend = 'X';
   }
 //dataToSend = 'X';  // Toggle between 'A' and 'B'
  delay(5);
}