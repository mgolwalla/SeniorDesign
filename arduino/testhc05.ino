
#include <SoftwareSerial.h>
char value;
int Tx = 4;       // connect BT module TX to 4
int Rx = 3;       // connect BT module RX to 3
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
