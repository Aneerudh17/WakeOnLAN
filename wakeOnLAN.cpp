#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "realme GT 2 Pro";
const char* password = "12341234"; 
const char* broadcastIp = "255.255.255.255";
const int udpPort = 9; 
byte macAddress[] = { 0x10, 0x68, 0x38, 0x11, 0xA5, 0x9F };
WiFiUDP Udp;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Udp.begin(udpPort);
}
void loop() {
  byte packet[102];
  memset(packet, 0xFF, 6); 
  for (int i = 6; i < 102; i += 6) {
    memcpy(packet + i, macAddress, 6); 
  }
  Udp.beginPacket(broadcastIp, udpPort);
  Udp.write(packet, sizeof(packet));
  Udp.endPacket();
  Serial.println("Magic Packet sent to wake PC!");
  delay(5000); 
}