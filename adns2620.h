/* Arduino ADNS2620 Library
 * Copyright 2010 SparkFun Electronic
 * Written by Ryan Owens
*/

#ifndef adns2620_h
#define adns2620_h

#include <avr/pgmspace.h>
#include "WProgram.h"

class ADNS2620
{
	public:
		ADNS2620(int sda, int scl);
		void begin();
		void sync();
		char read(char address);
		void write(char address, char value);
	private:
		int _sda;
		int _scl;
};

/* Register Map for the ADNS2620 Optical Mouse Sensor */
#define CONFIGURATION_REG   0x40
#define STATUS_REG          0x41
#define DELTA_Y_REG         0x42
#define DELTA_X_REG         0x43
#define SQUAL_REG           0x44
#define MAXIMUM_PIXEL_REG   0x45
#define MINIMUM_PIXEL_REG   0x46
#define PIXEL_SUM_REG       0x47
#define PIXEL_DATA_REG      0x48
#define SHUTTER_UPPER_REG   0x49
#define SHUTTER_LOWER_REG   0x4A
#define FRAME_PERIOD		0x4B

#endif