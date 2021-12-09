#include <Arduino.h>
#include "webserver.h"

void setup()
{
  	Serial.begin(9600);
  	while (!Serial);

	WebServer::Setup();
	WebServer::Start();

}

void loop()
{

}