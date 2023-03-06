String picommand; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12,OUTPUT);

}

void loop() {
  
  if (Serial.available()){
    picommand = Serial.readStringUntil('\n');

    if (picommand.equals("blue"))
    digitalWrite(12, HIGH);
  }

}
