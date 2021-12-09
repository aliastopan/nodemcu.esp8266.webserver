#ifndef WEBSERVER
#define WEBSERVER

#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <ESPAsyncWiFiManager.h>
#include <ArduinoJson.h>

// WiFi Manager IP          [ 192.168.4.1 ]
// WiFi Manager Password    [ 2-4-8-16-32-64 ]

const int port = 80;
const char* ssid = "NodeMCU WiFi";
const char* password = "248163264";
AsyncWebServer server(port);
DNSServer dns;

String header;

class WebServer{
    public:
    static void Setup()
    {
        AsyncWiFiManager authenticator(&server, &dns);
        authenticator.autoConnect(ssid, password);

        Serial.print("Authenticated: ");
        Serial.println(WiFi.localIP());
    }

    static void Start()
    {
        if (!LittleFS.begin())
	    {
		    Serial.println("Failed to mount flash file system");
		    return;
	    }

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		    request->send(LittleFS, "/index.html", String());
	    });

        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  		    request->send(LittleFS, "/style.css","text/css");
	    });

        server.begin();

    }
};

#endif