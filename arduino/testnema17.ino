// (pul, dir, ena)
// stepper motor 1 - (12,11,10)
//stepper motor 2 - (7,6,5)

void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,HIGH);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
}

void loop(){
    digitalWrite(12, HIGH);
    digitalWrite(7, HIGH);
    delayMicroseconds(750);
    digitalWrite(12, LOW);
    digitalWrite(7, LOW);
 }
