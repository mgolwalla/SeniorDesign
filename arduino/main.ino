#include <SoftwareSerial.h>
char value;
int Tx = 4;       // connect BT module TX to 4
int Rx = 3;       // connect BT module RX to 3
int LED = 13;
int endstopTopR = 2;
int endstopTopL = 8;
int endstopBot = 9;
String picommand;
SoftwareSerial bluetooth(Tx, Rx);

char tester;
char alreadyOn = '0';
int TopLeftFlag = 0;
int autoStart = 0;

int countBot = 0;
int BotFlag = 0;
int stopFlag = 0;
int BotCount = 0;
int pauseFlag = 0;
int resetFlag = 1;
long int t1;
long int t2;


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(endstopTopR, INPUT);
  pinMode(endstopTopL, INPUT);
  pinMode(endstopBot, INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  // Top Motor
  digitalWrite(11, LOW);
  // High = Clockwise
  // Low = Counter-Clockwise

  // Bottom Motor
  digitalWrite(6, LOW);
  // High = Clockwise
  // Low = Counter-Clockwise
}

void loop() {
  //Make sure we are at starting point
//    if ((checkOrigin() == 1) && (alreadyOn == '0') && (pauseFlag == 0)) {
//      checkInput();
//      //checkCam();
//    }
//    else if(pauseFlag == 1){
//      checkInput();
//    }
   checkInput();
   if(alreadyOn == '0'){
    checkCam();
   }
    if ((alreadyOn == '1') || (autoStart == 1)) { // Manual Start
      while (stopFlag == 0) {
        checkInput();
        if (TopLeftFlag == 0) {
          moveTopLeft();
        }
        else if (TopLeftFlag == 1) {
          moveTopRight();
        }
      }

      // Run Bot Motor
      if ((BotFlag == 0) && (stopFlag == 1) && (BotCount < 6)) { //Edit
        moveBotDown();
      }
      if (BotCount == 6) { //Edit
        moveBotTop();
      }
    }
  }

  void moveTopLeft() {
    // Top Motor moves Left
    digitalWrite(11, LOW); //Change Direction
    if (digitalRead(endstopTopL) == HIGH) { // Stop Condition
      TopLeftFlag = 1;
      return; //Stop
    }
    digitalWrite(12, HIGH);//Pulse Top Motor
    delayMicroseconds(100);
    // Off
    digitalWrite(12, LOW);//Top Motor
    delayMicroseconds(100);
  }


  void moveTopRight() {
    // Top Motor moves Right
    digitalWrite(11, HIGH); //Change Direction
    if (digitalRead(endstopTopR) == HIGH) {
      TopLeftFlag = 0;
      BotFlag = 0;
      stopFlag = 1;
      return; //Stop
    }
    digitalWrite(12, HIGH);//Pulse Top Motor
    delayMicroseconds(100);
    // Off
    digitalWrite(12, LOW);//Top Motor
    delayMicroseconds(100);
  }

  void moveBotDown() {
    // Bot Motor moves Down
    digitalWrite(6, HIGH); //Change Direction
    if (countBot > 5000) {
      BotFlag = 1;
      countBot = 0;
      stopFlag = 0;
      BotCount++;
      return; //Stop
    }
    digitalWrite(7, HIGH);//Pulse Bot Motor
    delayMicroseconds(750);
    // Off
    digitalWrite(7, LOW);//Bot Motor
    delayMicroseconds(1000);
    countBot++;
  }

  void moveBotTop() {
    // Bot Motor moves Top
    digitalWrite(6, LOW); //Change Direction
    if (digitalRead(endstopBot) == HIGH) { //Edit
      BotFlag = 1;
      countBot = 0;
      stopFlag = 1;
      BotCount = 0;
      alreadyOn = '0';
      autoStart = 0;
      t2 = millis();
      Serial.print("Time taken by the task: ");
      Serial.print(t2-t1);
      Serial.println(" milliseconds");
      return; //Stop
    }
    digitalWrite(7, HIGH);//Pulse Bot Motor
    delayMicroseconds(750);
    // Off
    digitalWrite(7, LOW);//Bot Motor
    delayMicroseconds(1000);

  }

  void checkInput() {
    // INPUT SETS stopFlag = 0
    if (bluetooth.available()) {
      tester = bluetooth.read(); //The only read point
      if ((tester == '1') && (alreadyOn == '0')) {
        // Condition occurs when On button is pressed and system is at origin (not cleaning)
        //Pushing the On button more than once does not affect anything in system
        //digitalWrite(LED, HIGH); // Debugger
        alreadyOn = '1';
        t1 = millis();
        stopFlag = 0;
        pauseFlag = 0;
      }
      else if ((tester == '2') && (alreadyOn == '1')) {
        // Condition occurs when Pause button is pressed
        alreadyOn = '0';
        stopFlag = 1;
        pauseFlag = 1;
      }
      else if ((tester == '0') && (alreadyOn == '0')) {
        // Condition occurs when Reset button is pressed
        alreadyOn = '1';
        resetFlag = 1;
      }
    }
  }

  void checkCam() {
    if (Serial.available()) {
      picommand = Serial.readStringUntil('\n');
      if (picommand.equals("blue")) {
        autoStart = 1;
      }
      else {
        autoStart = 0;
      }
    }
  }

  int checkOrigin() {
    if ((digitalRead(endstopTopR) == HIGH) && (digitalRead(endstopBot) == HIGH)) {
      return 1;
    }
    else if ((digitalRead(endstopTopR) == LOW) && (digitalRead(endstopBot) == LOW)) {
      return 0;
    }
  }

  void resetFunc() {
    // One at a time
    moveBotTop();

    moveTopRight();
  }
