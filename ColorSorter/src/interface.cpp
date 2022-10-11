/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
11.10.22, 14:16

Webinterface functions
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include "interface.h"
#include "sorter.h"


namespace interface
{
    WebServer ifsrv(80);

    void rh_root();
    void rh_color();
    void rh_on();
    void rh_off();
}


void interface::ap_init(const char *_ssid, const char *_psk)
{
    SPIFFS.begin();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(_ssid, _psk);
}

void interface::ws_init()
{
    ifsrv.on("/", HTTP_GET, rh_root);
    ifsrv.on("/color", HTTP_GET, rh_color);
    ifsrv.on("/on", HTTP_GET, rh_on);
    ifsrv.on("/off", HTTP_GET, rh_off);
    ifsrv.begin();
}

void interface::rh_root()
{
    auto file = SPIFFS.open("/index.html");
    ifsrv.streamFile(file, "text/html");
    file.close();
}

void interface::rh_color()
{
    char output[100];
    snprintf(output, 100, "%d", sorter::get_last_color());
    ifsrv.send(200, "text/html", output);
}

void interface::rh_on()
{
    ifsrv.send(200, "text/html", "on");
    sorter::on();
}

void interface::rh_off()
{
    ifsrv.send(200, "text/html", "off");
    sorter::off();
}

void interface::handle()
{
    ifsrv.handleClient();
}