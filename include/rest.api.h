#ifndef RESTAPI
#define RESTAPI

#include <LittleFS.h>
#include "server.config.h"
#include "board.h"

class API{
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
		    request->send(LittleFS, "/index.html", String());
	    });

        server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
  		    request->send(LittleFS, "/styles.css","text/css");
	    });

        server.begin();

    }
};

#endif