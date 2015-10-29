/*-----------------------------------------------------
Author:  --<>
Date: 2015-10-23
Description:

-----------------------------------------------------*/
unsigned long time;

void setup(){
    while(CONTROL_LINE==0){}
        //pinMode(USERLED, OUTPUT);

    

}
void loop(){
   CDC.printf("Time: ");
  time = millis();
  //prints time since program started
   CDC.printf("%u \r\n",time);
  // wait a second so as not to send massive amounts of data
      //toggle(USERLED);

  //delay(500);
  
}