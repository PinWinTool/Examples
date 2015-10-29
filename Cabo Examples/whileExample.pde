/*-----------------------------------------------------
Author:  --<>
Date: 2015-09-16
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
    int x = 0;

    while(x!=4)
     {

        //  digitalWrite(x,HIGH);
        toggle(x);
          x ++;
          }

}
