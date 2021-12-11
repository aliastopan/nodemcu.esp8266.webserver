#ifndef WEBSERVER
#define WEBSERVER

#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <ESPAsyncWiFiManager.h>
#include <ArduinoJson.h>
#include "board.h"

// WiFi Manager IP          [ 192.168.4.1 ]
// WiFi Manager Password    [ 2-4-8-16-32-64 ]

const int port = 80;
const char* ssid = "Einharan";
const char* password = "248163264";
AsyncWebServer server(port);
DNSServer dns;

const char* _ssid = "Wifi@Home";
const char* _password = "02062000";

class WebServer{
    public:
    static void SetupAuto()
    {
        WiFi.begin(_ssid, _password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Authenticating...");
        }

        Serial.print("Authenticated: ");
        Serial.println(WiFi.localIP());
    }

    static void Setup()
    {
        // AsyncWiFiManager authenticator(&server, &dns);
        // authenticator.autoConnect(ssid, password);

        WiFi.begin(_ssid, _password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Authenticating...");
        }

        Serial.print("Authenticated: ");
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