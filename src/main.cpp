#include <Arduino.h>
#include "rest.api.h"
#include "board.h"


void setup()
{
	Board::Setup();

	API::Setup();
	API::Start();

}

void loop()
{
	Board::Loop();
}