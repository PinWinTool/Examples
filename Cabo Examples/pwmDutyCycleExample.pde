/*-----------------------------------------------------
Author:  --<>
Date: 2015-10-21
Description:

-----------------------------------------------------*/
#define MYLED 11

u8 i = 0;
s8 dir;

void setup()
{
    // Frequency (Hz) must be high to avoid blinking effect
    PWM.setFrequency(20000);
}

void loop()
{
    // Duty Cycle from 0% to 50% and back
    if (i > 511) dir = -1;
    if (i <= 0) dir =  1;
    i = i + dir;
    // Duty Cycle is a percentage measure of the time that the LED is physically on.
    PWM.setDutyCycle(MYLED, i);
    // Delay of 25 ms
    delay(50);
}