#include <Wire.h>
#include "Adafruit_TCS34725.h"

//branché le capteur sur le port IC2 




#define redpin 3
#define greenpin 5
#define bluepin 6

#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];


int detect_color(float red, float green, float blue){
      // detection couleur
      if (red > 70 && green < 70 && blue < 70) {
        
        return 3; 
        }
      else if (red < 70 && green < 70 && blue > 70) {
        
        return 1; 
      }
      else if(red > 70 && green > 70 && blue > 70){
        
        return 2; 
      }
      else 
      {
        return 0;
      }
    }

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    Serial.begin(9600);
    

    

    // use these three pins to drive an LED
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);

    // thanks PhilB for this gamma table!
    // it helps convert RGB colors to what humans see
    for (int i = 0; i < 256; i++) {
        float x = i;
        x /= 255;
        x = pow(x, 2.5);
        x *= 255;

        if (commonAnode) {
            gammatable[i] = 255 - x;
        } else {
            gammatable[i] = x;
        }
        //Serial.println(gammatable[i]);
    }
}


void loop() {
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear); // variable clear obligatoire pour la fonction

    tcs.setInterrupt(true);  // turn off LED

  
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.print(blue);

    // Figure out some basic hex code for visualization
    uint32_t sum = clear;
    float r, g, b;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;
    Serial.print("\t");
    //Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX); 
    Serial.println();

    //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

    int detect = detect_color(red, green, blue);

    if (detect == 1)
    {
      Serial.print("BLEU");
    }
    else if (detect == 2)
    {
      Serial.print("BLANC");
    }
    else if(detect == 3)
    {
      Serial.print("ROUGE");
    }
    else if(detect == 0)
    {
      Serial.print("Mauvaise couleur detecter");
    }

    //Serial.print(detect); //test voir la valeur de la fonction detect_color si il y a un bug

  
    
    

    analogWrite(redpin, gammatable[(int)r]);
    analogWrite(greenpin, gammatable[(int)g]);
    analogWrite(bluepin, gammatable[(int)b]);
}
