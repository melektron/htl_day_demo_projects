/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
10.10.22, 15:40
*/

#include <Arduino.h>

#define S0 17
#define S1 18
#define S2 19
#define S3 23
#define sensorOut 25

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void sensor_init()
{
    // Setting the outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Setting the sensorOut as an input
    pinMode(sensorOut, INPUT);

    // Setting frequency scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // Begins serial communication
    Serial.begin(9600);
}
void sensor_measure()
{
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);

    // Reading the output frequency
    redFrequency = pulseIn(sensorOut, LOW);

    // Printing the RED (R) value
    delay(1);

    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);

    // Reading the output frequency
    greenFrequency = pulseIn(sensorOut, LOW);

    // Printing the GREEN (G) value
    delay(1);

    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);

    // Reading the output frequency
    blueFrequency = pulseIn(sensorOut, LOW);

    // Printing the BLUE (B) value
    Serial.printf("%3d, %3d, %3d\n", redFrequency, greenFrequency, blueFrequency);
}