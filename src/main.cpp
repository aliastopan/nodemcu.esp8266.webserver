#include <Arduino.h>
#include "rest.api.h"
#include "board.h"

void setup()
{
  	Serial.begin(9600);
  	while (!Serial);

	API::Setup();
	API::Start();

}

void loop()
{

}