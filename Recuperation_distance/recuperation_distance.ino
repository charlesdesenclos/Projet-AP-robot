#include "Ultrasonic.h" // Inclusion de la bibliothèque

// Branché sur le port D7 du shield
 
Ultrasonic ultrasonic(7);

void setup()
{
    Serial.begin(9600);
}
void loop()
{
  
    long PorteeCentimetres;
 
    Serial.println("La distance aux obstacles devant est : ");
 
 
    PorteeCentimetres = ultrasonic.MeasureInCentimeters(); // deux mesures doivent garder un intervalle
    
    //Affichage de la portée en centimètres
    
    Serial.print(PorteeCentimetres);//0~400cm
    Serial.println(" cm");
    delay(250);
}
