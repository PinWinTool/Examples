/*-----------------------------------------------------
Author:  --<>
Date: 2015-11-11
Description:

-----------------------------------------------------*/

// Variables

u16 address = 0;
u8 value;


void setup() {

    pinMode(USERLED,OUTPUT);
}

void loop() {
        // leyendo la memoria EEPROM en la localidad 0x00
        value = EEPROM.read(address);
    // exhibiendo el valor guardado en la memoria
    CDC.printf("%u\r\n",value);
    // si el valor es 255 reiniciar a 0
    if(value==255){
            value=0;
        }
        //aumentar el valor de la variable en uno
            value+=1;
// escribir el nuevo valor en la memoria EEPROM com la direccion 0x00
            EEPROM.write(address , value);



    delay(100);
    toggle(USERLED);

    

}
