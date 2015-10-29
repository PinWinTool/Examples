/*----------------------------------------------------- 
Author:  --<Pinwintool>
Date: Sat May 09 20:54:01 2015
Description:Leer Sensor Ultrasonico y Escribir posicion de un ServoMotor via CDC


-----------------------------------------------------*/
#define echoPin  1
#define trigPin 0
#define servoPin 7


unsigned char(bytes_recibidos);
char buffer[20];
u8 datos[5];
u8 numero;

void leer_posicion(void){
int i=0;

numero =0;
toggle(USERLED);

for(i=0;i<bytes_recibidos;i++){
    if(buffer[i]>=48 && buffer[i]<58){
        
        datos[i]=(buffer[i]-48);
        numero=numero*10;
        numero+=datos[i];
        }
}

 buffer[bytes_recibidos]=0;
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void setup() {
    //run once:
    while(CONTROL_LINE==0){}
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(USERLED,OUTPUT);
    servo.attach(servoPin);
    servo.setMaximumPulse(servoPin,2000);
    servo.setMinimumPulse(servoPin,1000);

        }


void loop() {
    //run repeatedly:
long duration, cm;
 if((bytes_recibidos=CDC.read(buffer))>0)//si se recibe un dato
     leer_posicion();
     
     
 servo.write(servoPin, numero);
delay(15);

//Triger
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

// echo pin
  duration = pulseIn(echoPin, HIGH, 10000);
  cm = microsecondsToCentimeters(duration);
 if (CONTROL_LINE) CDC.printf("%u\r\n",cm);
    }   