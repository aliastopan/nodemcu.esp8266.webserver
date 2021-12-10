#include <Arduino.h>
#include "webserver.h"
#include "board.h"

void setup()
{
  	Serial.begin(9600);
  	while (!Serial);

	WebServer::SetupAuto();
	WebServer::Start();

}

void loop()
{

}