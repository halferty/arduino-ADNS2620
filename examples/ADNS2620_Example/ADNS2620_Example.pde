/* ADNS2620 Example Sketch
*  Demonstrates how to use the ADNS2620 Library to interface with the mouse sensor
*  on the ADNS2620 evaluation board from SparkFun Electronics
*
*  More register definitions are located in the 'adns2620.h' file. Read the
*  ADNS2620 datasheet to understand how to use the registers.
*
*  After loading the sketch to the ADNS2620 evaluation board, open the serial terminal
*  using a baud rate of 9600 to see the output from the ADNS2620 sensor.
*
*  Written by Ryan Owens
*  11/4/10
*  SparkFun Electronics
*/
//Add the ADNS2620 Library to the sketch.
#include <adns2620.h>

//Name the ADNS2620, and tell the sketch which pins are used for communication
ADNS2620 mouse(18,19);

//This value will be used to store information from the mouse registers.
unsigned char value=0;

void setup()
{
	//Initialize the ADNS2620
    mouse.begin();
    delay(100);
	//A sync is performed to make sure the ADNS2620 is communicating
    mouse.sync();
	//Put the ADNS2620 into 'always on' mode.
    mouse.write(CONFIGURATION_REG, 0x01);
    
	//Create a serial output.
    Serial.begin(9600);
}

void loop()
{
	//The DELTA_X_REG and DELTA_Y_REG store the x and y movements detected by the sensor
	
	//Read the DELTA_X_REG register and store the result in 'value'
    value = mouse.read(DELTA_X_REG);
	//Print 'value' to the serial port.
    Serial.print("X:");
    Serial.print(value, HEX);
    Serial.print('\t');
    
	//Read the DELTA_Y_REG register and store the result in 'value'
    value = mouse.read(DELTA_Y_REG);
	//Print 'value' to the serial port.
    Serial.print("Y:");
    Serial.println(value, HEX);

    delay(10);    
}
    
    


