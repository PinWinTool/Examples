/*-----------------------------------------------------
Author:  --<>
Date: 2015-09-15
Description:

-----------------------------------------------------*/

void setup() {
    // put your setup code here, to run once:
int i;
    for (i=0;i<4;i++)
        {
        pinMode(i,OUTPUT);
        digitalWrite(i,LOW);
        }


    
}

void loop() {
    // put your main code here, to run repeatedly:
    int j;
    int valor;
    valor=analogRead(5);
    switch (valor)
    {
        case 512:
        
        for (j=0;j<4;j++)
        {
                digitalWrite(j,HIGH);

        
        break;
        }
        case 0:
        
      for (j=4;j<0;j--)
        {
                digitalWrite(j,LOW);

        }  
        break;
        default:
        break;
        
    }

}
