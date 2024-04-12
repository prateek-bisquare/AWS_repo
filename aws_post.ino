#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "BSQ-DEMO"
#define STAPSK  "Bisquare@123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "zqvdblr8ak.execute-api.ap-south-1.amazonaws.com";   // do not include "https://"
String url = "/v1";

const int httpsPort = 443;
unsigned long uptime;

// Use web browser to view and copy  SHA1 fingerprint of the certificate 
const char fingerprint[] PROGMEM = "BD D3 04 69 A6 C5 87 20 66 21 01 4A 73 03 7E 64 9D 20 99 5B";

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  int t =  random(30,110); // fake number range, adjust as you like
  int h =  random(50,100);
  String x="#s00362E0904D400FF00E0000009930177017001A5000B0017015D03DF01A4270F00E300DB03E80004270F000000C013EC13EC13EC0000F19FE86D";
  String postData = "Data=" + x;

  client.print("POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + postData.length() + "\r\n\r\n" +
               postData);

  Serial.println("POST request sent");

  // You may read response here if needed
}

void loop() {
  // Your loop code here
}
