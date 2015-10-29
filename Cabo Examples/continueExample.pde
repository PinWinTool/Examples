/*-----------------------------------------------------
Author:  --<>
Date: 2015-09-20
Description:

-----------------------------------------------------*/
#define servoPin 7

void setup() {
    // put your setup code here, to run once:

    servo.attach(servoPin);
    servo.setMaximumPulse(servoPin,2000);
    servo.setMinimumPulse(servoPin,1000);

}

void loop() {
    // put your main code here, to run repeatedly:
    int x;
    for (x = 0; x < 179; x ++)
{
    if (x > 40 && x < 120){      // el servo motor saltara de valores 40 a 120
        continue;
    }
     
     servo.write(servoPin, x);

    delay(50);
}

}
