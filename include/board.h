#ifndef BOARD
#define BOARD

#include <easing.h>

#define SUPERFLUX D4

bool isOn = false;
bool isLapse = false;
unsigned long start;
unsigned long end;
unsigned long lapse;
unsigned long duration = 3000;
float t;


class Board
{
    public:
        static void Setup()
        {
            Serial.begin(9600);
  	        while (!Serial);
        }

        static void Loop()
        {
            if(isOn)
            {

                t = (float)((float)lapse - (float)start)/(((float)start+(float)duration) - (float)start);
                easingFunction easingFunction = getEasingFunction(EaseInCirc);
                float progress = easingFunction(t);
                Serial.print("PWM: ");
                Serial.print(255 * progress);
                Serial.print(" : ");
                Serial.print(progress);
                Serial.println("%: ");

                analogWrite(SUPERFLUX, 255 * progress);

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
                        t = 0.00;
                    }
                }
            }
            else
                analogWrite(SUPERFLUX, 0);
        }
};



#endif