#ifndef RESTAPI
#define RESTAPI

#include <LittleFS.h>
#include "server.config.h"
#include "board.h"

class API
{
    private:
        static void NotFound(AsyncWebServerRequest *request)
        {
            request->send(404, "text/plain", "not found");
        }

        static String Processor(const String& var)
        {
            if(var == "STATUS"){
                return String(isOn);
            }
            return String();
        }

    public:
        static void Setup()
        {
            WiFi.begin(_ssid, _password);
            while (WiFi.status() != WL_CONNECTED) {
                delay(1000);
                Serial.println("Connecting to Access Point...");
            }

            Serial.print("Stand By: ");
            Serial.println(WiFi.localIP());
        }

    static void Start()
        {
            if (!LittleFS.begin())
            {
                Serial.println("failed to mount flash file system");
                return;
            }

            server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send(LittleFS, "/index.html", String(), false, Processor);
            });

            server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send(LittleFS, "/styles.css","text/css");
            });

            server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send(200, "text/plain", String(isOn).c_str());
            });

            server.on("/read", HTTP_GET, [](AsyncWebServerRequest *request){
                String message;
                if(request->hasParam("message"))
                {
                    message = request->getParam("message")->value();
                    isOn = message == "on" ? true : false;

                    request->send(200, "text/plain", message);
                }
                else
                {
                    request->send(404, "text/plain", "not found");
                }
            });

            server.onNotFound(NotFound);
            server.begin();
        }
};

#endif