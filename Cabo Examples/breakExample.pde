/*-----------------------------------------------------
Author:  --<>
Date: 2015-09-19
Description:

-----------------------------------------------------*/

void setup() {
    pinMode(11,OUTPUT);
pinMode(0,INPUT);
    
}

void loop() {
   int threshold=100; //referencia del sensor
    for (x = 0; x < 255; x ++)
{
    analogWrite(11,512);    // señal cuadrada al 50% por pin 11
    sens = analogRead(0);  
    if (sens > threshold){      // Valor comparado con el sensor
       x = 0;
       break; // sale del ciclo si la condicion se cumple
    }  
    delay(50);
}
}
