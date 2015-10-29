/*-----------------------------------------------------
Author:  --<>
Date: 2015-10-04
Description:

-----------------------------------------------------*/
void blink13()
{
	toggle(13); //el pin 13 oscilara de positivo a negativo y viceversa
}
 
 void blinkU()
{
	toggle(USERLED); // el led del usuario oscilara de positivo a negativo y viceversa
}
 
 
void setup()
{
       pinMode(13, OUTPUT);
       OnTimer0(blink13, INT_MILLISEC, 500); // Usa el Timer0 para la funcion toggle en el pin 13 cada 500 ms
       OnChangePin0(blinkU,INT_RISING_EDGE );//  llama al toogle para el led del usario cada que lo conectado al pin0 pase de alto a bajo.
}
 
void loop()
{

}
