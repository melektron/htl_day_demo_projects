#include <Arduino.h>
#include <FastLED.h>

#define trig 14
#define echo 16
#define NUM_LED 30
#define DP 27 

CRGB leds[NUM_LED];

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  FastLED.addLeds<NEOPIXEL, DP>(leds, NUM_LED);
  FastLED.setBrightness(10);
}


void loop() {
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.println(distance);

  // Displays the distance on the Slide
  //3.35 distance LED - LED 
  int light_LED = distance/3.35;
  for (int i=0; i < NUM_LED; i++)
  {
    leds[i] = i <= light_LED ? (CRGB)CHSV(i*(255/NUM_LED),255,255) : CRGB::Black; 
  }
  FastLED.show();
  delay(20);
}