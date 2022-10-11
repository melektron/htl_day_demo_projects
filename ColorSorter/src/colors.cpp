#include "colors.h"


// Stores frequency read by the photodiodes
int redFrequency;
int greenFrequency;
int blueFrequency;

// Stores the red. green and blue colors
int redColor;
int greenColor;
int blueColor;


#define r_min 12
#define r_max 170
#define g_min 13
#define g_max 197
#define b_min 11
#define b_max 160


void colors::pins_init()
{
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}


int mostFrequent(int* arr, int n)
{
    // code here
    int maxcount = 0;
    int element_having_max_freq;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j])
                count++;
        }
 
        if (count > maxcount) {
            maxcount = count;
            element_having_max_freq = arr[i];
        }
    }
 
    return element_having_max_freq;
}


int colors::detect_color(int detail = 10)
{
  /*
  returns:
  0: green
  1: yellow
  2: orange
  3: red
  4: nothing
  */
  int detected_colors[detail];

  for (int i = 0; i <= detail; i++) {
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    
    // Reading the output frequency
    redFrequency = pulseIn(sensorOut, LOW);
    // Remaping the value of the RED (R) frequency from 0 to 255
    // You must replace with your own values. Here's an example: 
    // redColor = map(redFrequency, 70, 120, 255,0);
    redColor = map(redFrequency, r_min, r_max, 255,0);
    
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    greenFrequency = pulseIn(sensorOut, LOW);
    // Remaping the value of the GREEN (G) frequency from 0 to 255
    // You must replace with your own values. Here's an example: 
    // greenColor = map(greenFrequency, 100, 199, 255, 0);
    greenColor = map(greenFrequency, g_min, g_max, 255, 0);
  
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    blueFrequency = pulseIn(sensorOut, LOW);
    // Remaping the value of the BLUE (B) frequency from 0 to 255
    // You must replace with your own values. Here's an example: 
    // blueColor = map(blueFrequency, 38, 84, 255, 0);
    blueColor = map(blueFrequency, b_min, b_max, 255, 0);

    // Checks the current detected color
    // for green: 140 < x < 185, 174 - 200, 102 < x < 170
    // for yellow: 330 < x < 337, 327 < 333, 325 < x < 332
    // for orange: 329 < x < 335, 315 < x < 330, 322 < x < 330
    // for red: 323 < x < 329, 311 < x < 319, 319 < x < 325

    Serial.print(redColor); Serial.print(" - "); Serial.print(greenColor); Serial.print(" - "); Serial.print(blueColor); Serial.print("  ");
    if (
      140 < redColor && redColor < 185
      && 169 < greenColor && greenColor < 200
      && 102 < blueColor && blueColor < 170
      )
    {
      Serial.println(" - green");
      detected_colors[i] = 0;
    }

    else if (
      187 < redColor && redColor < 220
      && 176 < greenColor && greenColor < 210
      && 131 < blueColor && blueColor < 191
      )
    {
      Serial.println(" - yellow");
      detected_colors[i] = 1;
    }

    else if (
      192 < redColor && redColor < 220
      && 135 < greenColor < 194
      && 97 < blueColor < 173
      )
    {
      Serial.println(" - orange");
      detected_colors[i] = 2;
    }

    else if (
      160 < redColor && redColor < 198
      && 72 < greenColor < 171
      && 71 < blueColor < 166
      )
    {
      Serial.println(" - red");
      detected_colors[i] = 3;
    }

    else
    {
      Serial.println(" - nothing");
      detected_colors[i] = 4;
    }
  }

  // check which color was detected the most often
  return mostFrequent(detected_colors, sizeof(detected_colors) / sizeof(detected_colors[0]));
}
