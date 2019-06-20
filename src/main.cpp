// WiFi includes
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
//#include <NTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

// OTA Includes
#include <ArduinoOTA.h>

// Custom Includes
#include "config.h"


// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
ESP8266WebServer server(80);
/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);
// DNS server
DNSServer dnsServer;

// wifi, client instances
WiFiClient espClient;

void configureOTA() {
  //#ifdef OTA

  // Port defaults to 8266
  //ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    Serial.end();
  });


  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  });
  ArduinoOTA.setHostname(myHostname);
  //ArduinoOTA.setRebootOnSuccess(false);
  ArduinoOTA.begin();
#ifdef SERIALDEBUG
  Serial.println(" OTA ");
#endif
}


void setupAP() {
  digitalWrite(LED_BUILTIN, LOW);   // toggle LED

  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, softAP_password);
  delay(500); // Without delay I've seen the IP address blank
  digitalWrite(LED_BUILTIN, HIGH);   // toggle LED
}

void setupCore() {
#ifdef SERIALDEBUG
  Serial.println("Setup Core:");
#endif
//  loadCredentials(); // Load WLAN credentials from network

//  if (strlen(ssid) > 0) {
//    connectWifi();
//  }
  setupAP();

  // Setup MDNS responder
  int connRes = WiFi.waitForConnectResult();
  if (MDNS.begin(myHostname)) {
    /* Setup the DNS server redirecting all the domains to the apIP */
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    if ( connRes == WL_CONNECTED ) {
      dnsServer.start(DNS_PORT, "*", WiFi.localIP());
    } else {
      dnsServer.start(DNS_PORT, "*", apIP);
    }
    MDNS.addService("http", "tcp", 80);
#ifdef SERIALDEBUG
    Serial.print(" MDNS ");
#endif
  }
//  startHTTP();
  configureOTA();
#ifdef SERIALDEBUG
  Serial.println("Setup Core Complete!");
#endif
}

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
#ifdef SERIALDEBUG
  Serial.begin(115200);
#endif

#ifndef SERIALDEBUG
  Serial.setDebugOutput(true);
#endif
  WiFi.disconnect(true);
#ifdef SERIALDEBUG
  Serial.println("Wifi Disconnect");
#endif
  WiFi.softAPdisconnect(true);
  WiFi.persistent(false);
  delay(500);
  WiFi.mode(WIFI_AP_STA);
#ifdef SERIALDEBUG
  Serial.println("Wifi Setmode AP_STA");
#endif
  delay(500);
  setupCore();
  // Set Hostname.
  String hostname(myHostname);
  WiFi.hostname(myHostname);

  
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print(".");
  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print(".");
   // wait for a second
  delay(1000);

}




