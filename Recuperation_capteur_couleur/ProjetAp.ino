#include <Wire.h>
#include "Adafruit_TCS34725.h" //inclusion de la bibliothèque

//branché le capteur sur le port IC2 


//règlage des pins 

#define redpin 3
#define greenpin 5
#define bluepin 6

#define commonAnode true

//pour le RGB
byte gammatable[256];

/*------------------------------------------------------------------------------*/

// la fonction detect_color est utilisé pour donner la couleur souhaité : bleu(1), blanc(2), rouge(3) sinon la fonction renvoie 0
//fonction pour Groupe-5: Stratégie de détection du sens de marche à partir d'un code couleur au sol

int detect_color(float red, float green, float blue)
{
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


/*------------------------------------------------------------------------------*/


 

//appelle de la bibliotèque

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    Serial.begin(9600);
    

    

    // utilisez ces trois broches pour piloter une LED, mis en sortie
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);

   
    // il aide à convertir les couleurs RVB en ce que les humains voient
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
        //Serial.println(gammatable[i]); // pour voir la valeur  si problème
    }
}


void loop() {
    uint16_t clear, red, green, blue; // déclaration des variables pour les couleurs

    tcs.setInterrupt(false);      // La LED éteinte quand c'est false

    delay(60);  // prend 60 ms à lire

    tcs.getRawData(&red, &green, &blue, &clear); // variable clear obligatoire pour la fonction

    tcs.setInterrupt(true);  // La LED allumé quand c'est false


    // Affichage des valeurs des couleurs pour rouge, vert et bleue
      
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.print(blue);

    
   
    Serial.print("\t");
   
    Serial.println();

    


/*------------------------------------------------------------------------------*/

//appelle de la fonction pour Groupe-5: Stratégie de détection du sens de marche à partir d'un code couleur au sol


    int detect = detect_color(red, green, blue); //appele de la fonction


   // gére ce que renvoie la fonction
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


/*------------------------------------------------------------------------------*/

  
    
    
}
