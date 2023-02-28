
#include <SoftwareSerial.h>
char value;
int Tx = 5;       // connect BT module TX to 5
int Rx = 4;       // connect BT module RX to 4
int LED = 13;
SoftwareSerial bluetooth(Tx, Rx);

void setup() {
 
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  
  if (bluetooth.available()) {
    
    value = bluetooth.read();
    
    if (value =='1') {
      digitalWrite(LED, HIGH);
      bluetooth.println(" LED on");
    }
    
    if (value =='0') {
      digitalWrite(LED, LOW);
      bluetooth.println("LED off");
    }
    
  }
}
