#include <Servo.h>
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "mGOEjkvWfhwC2yRJC-PPfytzOzWYUUYZ";

//Define the pins of the color sensor
#define s0 23 //S0 pin of the sensor on Arduino pin#2 
#define s1 18 //S1 pin of the sensor on Arduino pin#3 
#define s2 18 //S2 pin of the sensor on Arduino pin#4 
#define s3 17 //S3 pin of the sensor on Arduino pin#5
#define sensorOut 16 //Output pin of the sensor on Arduino pin#6 
#define taster 22

//Variable to save the data coming from the sensorOut
int frequency = 0;
int tasterstate;
// Variable to save the color
byte identifiedColor = 0;

//Declaring Servos

Servo feedingServo;
Servo decisionServo;

//Declaring general delays
byte smallDelay_ms = 5;
byte mediumDelay_ms = 20; //30
byte bigDelay_ms = 2000; //1000
byte veryBigDelay_ms = 2000;


//Delcaring position of the feederServo
byte pos1FeederServo = 6;
byte pos2FeederServo = 100;
byte pos3FeederServo = 180;

//Delcaring position of the decisionServo
byte decisionServo_RED = 22;
byte decisionServo_ORANGE = 55;
byte decisionServo_GREEN = 90;
byte decisionServo_YELLOW = 127;
byte decisionServo_PURPLE = 165;


void setup() {

  //Set the pins of the Color Sensor
  pinMode (s0, OUTPUT);
  pinMode (s1, OUTPUT);
  pinMode (s2, OUTPUT);
  pinMode (s3, OUTPUT);
  pinMode (sensorOut, INPUT);
  pinMode(taster, INPUT_PULLUP);

  //Using at 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  //Attaching the Servos
  feedingServo.attach (26);
  decisionServo.attach(27);

  //Set the serial communication in bytes per second
  Serial.begin(9600);

  Blynk.setDeviceName("Skittles");

  Blynk.begin(auth);

}//Close setup

void loop() {

Blynk.run();

tasterstate = digitalRead(taster);

if (tasterstate == 0)
{
  begin();
}
else home();

}
void home()
{
  identifiedColor = 0;
  decisionServo.write(90);
  feedingServo.write(8);

}
void movefeed()
{
  delay(bigDelay_ms);
  //Move Feeding servo to exit position
  for (int i = pos2FeederServo; i < pos3FeederServo; i++) {

    feedingServo.write (i);
    delay (mediumDelay_ms);

  }//Close for loop - Servo to Exit Position

  //Delay to return servo
  delay(bigDelay_ms);


  //Return the Feeding Servo to initial position
  for (int i = pos3FeederServo; i > pos1FeederServo ; i--) {

    feedingServo.write (i);
    delay (smallDelay_ms);
  }//Close for loop - Servo initial Position

  identifiedColor = 0;
  delay (veryBigDelay_ms);

}
void begin()
{
   //Write "steps" of 1 degree to the servo until pos2 (Sensor position)
  for (int i = pos1FeederServo; i < pos2FeederServo ; i++) {

    feedingServo.write (i);
    delay (mediumDelay_ms);

  }//close for loop

  //Delay to stabilize readings
  delay(bigDelay_ms);

  //We launch the Function getTheColor
  identifiedColor = getTheColor();
  Serial.println(identifiedColor);

  switch (identifiedColor) {
    //Case for Red
    case 1:
      decisionServo.write (decisionServo_RED);
      movefeed();
      break;

    //Case for Orange
    case 2:
      decisionServo.write (decisionServo_ORANGE);
      movefeed();
      break;

    //Case for Green
    case 3:
      decisionServo.write (decisionServo_GREEN);
      movefeed();
      break;

    //Case for Yellow
    case 4:
      decisionServo.write (decisionServo_YELLOW);
      movefeed();
      break;

    //Case for Purple
    case 5:
      decisionServo.write (decisionServo_PURPLE);
      movefeed();
      break;

  default:
  home(); 
  }
 
}  

int getTheColor() {

  //---Read RED values... S2 LOW - S3 LOW---
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int redValue = frequency;

  Serial.print("R=");
  Serial.print(redValue);
  Serial.print("  ");

  delay(50);

  //---Read Green values ... S2 LOW - S3 HIGH---
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int greenValue = frequency;

  Serial.print("G=");
  Serial.print(greenValue);
  Serial.print("  ");

  delay(50);


  //---Read Blue values ... S2 HIGH - S3 LOW---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int blueValue = frequency ;

  Serial.print("B=");
  Serial.print(blueValue);
  Serial.print("  ");

  delay(50);


    //---Read Clear values ... S2 HIGH - S3 HIGH---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int clearValue = frequency ;

  Serial.print("C=");
  Serial.print(clearValue);
  Serial.println("  ");

  delay(50);


  //////////Parameters for Red//////////
  if (redValue<13 & redValue>=11 & clearValue<23 & clearValue>19 & blueValue<7 & blueValue>3 & greenValue<19 & greenValue>=16) {
    identifiedColor = 1; // Red
  }

  //////////Parameters for Orange//////////
  if (redValue<11 & redValue>7 & clearValue<20 & clearValue>15 & blueValue<5 & blueValue>3) {
    identifiedColor = 2; // Orange
  }


  //////////Parameters for Green//////////
  if (blueValue<6 & blueValue>=3 & clearValue<19 & clearValue>11 & redValue<=14& redValue>9 & greenValue<22 & greenValue>13) {
    identifiedColor = 3; // Green
  }

  //////////Parameters for Yellow//////////
  if (redValue<10 & redValue>6 & clearValue<10 & clearValue>7 & blueValue<3 & blueValue>1) {
    identifiedColor = 4; // Yellow
  }

  //////////Parameters for Purple//////////
  if (redValue<19 & redValue>13  & clearValue<23 & clearValue>19 & blueValue<=6 & blueValue>=4 & greenValue<=18 & greenValue>15) {
    identifiedColor = 5; // Purple
  }
  
  //--- Return the value found---
  return identifiedColor;

}//Close Function getTheColor
