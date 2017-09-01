/* Arduino ADNS2620 Library
 * Can be used to interface between an ATmega328 (Arduino) and the ADNS2620 Mouse Sensor
 * Copyright 2010 SparkFun ElectronicS
 * Written by Ryan Owens
*/

#include <avr/pgmspace.h>
#include "adns2620.h"
#include "WProgram.h"

//Constructor sets the pins used for the mock 'i2c' communication
ADNS2620::ADNS2620(int sda, int scl)
{
	_sda = sda;
	_scl = scl;
}

//Configures the communication pins for their initial state
void ADNS2620::begin()
{
	pinMode(_sda, OUTPUT);
	pinMode(_scl, OUTPUT);
}

//Essentially resets communication to the ADNS2620 module
void ADNS2620::sync()
{
    digitalWrite(_scl, HIGH);
    delay(1);
	digitalWrite(_scl, LOW);
    delay(1);
	digitalWrite(_scl, HIGH);
    delay(100);
}

//Reads a register from the ADNS2620 sensor. Returns the result to the calling function.
//Example: value = mouse.read(CONFIGURATION_REG);
char ADNS2620::read(char address)
{
    char value=0;
	pinMode(_sda, OUTPUT); //Make sure the SDIO pin is set as an output.
    digitalWrite(_scl, HIGH); //Make sure the clock is high.
    address &= 0x7F;    //Make sure the highest bit of the address byte is '0' to indicate a read.
 
    //Send the Address to the ADNS2620
    for(int address_bit=7; address_bit >=0; address_bit--){
        digitalWrite(_scl, LOW);  //Lower the clock
        pinMode(_sda, OUTPUT); //Make sure the SDIO pin is set as an output.
        
        //If the current bit is a 1, set the SDIO pin. If not, clear the SDIO pin
        if(address & (1<<address_bit)){
            digitalWrite(_sda, HIGH);
        }
        else{
            digitalWrite(_sda, LOW);
        }
        delayMicroseconds(10);
        digitalWrite(_scl, HIGH);
        delayMicroseconds(10);
    }
    
    delayMicroseconds(120);   //Allow extra time for ADNS2620 to transition the SDIO pin (per datasheet)
    //Make SDIO an input on the microcontroller
    pinMode(_sda, INPUT);	//Make sure the SDIO pin is set as an input.
	digitalWrite(_sda, HIGH); //Enable the internal pull-up
        
    //Send the Value byte to the ADNS2620
    for(int value_bit=7; value_bit >= 0; value_bit--){
        digitalWrite(_scl, LOW);  //Lower the clock
        delayMicroseconds(10); //Allow the ADNS2620 to configure the SDIO pin
        digitalWrite(_scl, HIGH);  //Raise the clock
        delayMicroseconds(10);
        //If the SDIO pin is high, set the current bit in the 'value' variable. If low, leave the value bit default (0).    
		//if((ADNS_PIN & (1<<ADNS_sda)) == (1<<ADNS_sda))value|=(1<<value_bit);
		if(digitalRead(_sda))value |= (1<<value_bit);

    }
    
    return value;
}	

//Writes a value to a register on the ADNS2620.
//Example: mouse.write(CONFIGURATION_REG, 0x01);
void ADNS2620::write(char address, char value)
{
	pinMode(_sda, OUTPUT);	//Make sure the SDIO pin is set as an output.
    digitalWrite(_scl, HIGH);          //Make sure the clock is high.
    address |= 0x80;    //Make sure the highest bit of the address byte is '1' to indicate a write.

    //Send the Address to the ADNS2620
    for(int address_bit=7; address_bit >=0; address_bit--){
        digitalWrite(_scl, LOW); //Lower the clock
        
        delayMicroseconds(10); //Give a small delay (only needed for the first iteration to ensure that the ADNS2620 relinquishes
                    //control of SDIO if we are performing this write after a 'read' command.
        
        //If the current bit is a 1, set the SDIO pin. If not, clear the SDIO pin
        if(address & (1<<address_bit))digitalWrite(_sda, HIGH);
        else digitalWrite(_sda, LOW);
        delayMicroseconds(10);
        digitalWrite(_scl, HIGH);
        delayMicroseconds(10);
    }
    
    //Send the Value byte to the ADNS2620
    for(int value_bit=7; value_bit >= 0; value_bit--){
        digitalWrite(_scl, LOW);  //Lower the clock
        //If the current bit is a 1, set the SDIO pin. If not, clear the SDIO pin
        if(value & (1<<value_bit))digitalWrite(_sda, HIGH);
        else digitalWrite(_sda, LOW);
        delayMicroseconds(10);
        digitalWrite(_scl, HIGH);
        delayMicroseconds(10);
    }
}