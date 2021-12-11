#include <Arduino.h>
#include "rest.api.h"
#include "board.h"

#include <easing.h>

void setup()
{
  	Serial.begin(9600);
  	while (!Serial);

	API::Setup();
	API::Start();

}

void loop()
{
	if(isOn)
	{
		analogWrite(SUPERFLUX, 255);

		t = (float)((float)lapse - (float)start)/(((float)start+(float)duration) - (float)start);
		Serial.print("t: ");
		Serial.println(t);


		if(!isLapse)
		{
			start = millis();
			Serial.print("Start: ");
			Serial.println(start);
			isLapse = true;
		}
		else
		{
			lapse = millis();
			if(lapse >= start + duration)
			{
				Serial.print("Lapse: ");
				Serial.println(lapse);
				Serial.print("Duration: ");
				Serial.println(lapse - start);
				isLapse = false;
				isOn = false;
			}
		}
	}
	else
		analogWrite(SUPERFLUX, 0);

}