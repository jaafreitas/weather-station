#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "settings.h"
#include "debug.h"

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// Send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address) {
  // Set all bytes in the buffer to 0.
  memset(packetBuffer, 0, NTP_PACKET_SIZE);

  // Initialize values needed to form NTP request.
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0;          // Stratum, or type of clock
  packetBuffer[2] = 6;          // Polling Interval
  packetBuffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // All NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, NTP_PORT);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

time_t getNTPTime() {
  // I don't know why, but it crashes if we use time functions during update.
  debugMsg(false, "NTP time sync... ");

  IPAddress timeServerIP;
  // Get a random server from the pool.
  WiFi.hostByName(NTP_SERVER, timeServerIP);

  // Discard any previously received packets.
  while (Udp.parsePacket() > 0);

  sendNTPpacket(timeServerIP);

  uint32_t beginWait = millis();
  while (millis() - beginWait < 1000) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Udp.read(packetBuffer, NTP_PACKET_SIZE);

      // The timestamp starts at byte 40 of the received packet and is four bytes,
      // or two words, long. First, extract the two words:
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // Combine the four bytes (two words) into a long integer,
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;

      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      debugMsg(false, "Ok.\n");

      return secsSince1900 - seventyYears;
    }
  }
  debugMsg(false, "No NTP Response.\n");
  return 0;
}

void setupNTPClient() {
  Udp.begin(NTP_LOCALPORT);
  setSyncProvider(getNTPTime);
  setSyncInterval(NTP_INTERVAL);
}

