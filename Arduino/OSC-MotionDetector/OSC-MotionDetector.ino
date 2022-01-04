#include <OSCMessage.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>

static int sensorPin = 2;

EthernetUDP Udp;

//the Arduino's IP
IPAddress ip(23, 0, 0, 2);
//destination IP
IPAddress outIp(23, 0, 0, 1);
const unsigned int outPort = 2323;

byte mac[] = 
{  
  0x90, 0xA2, 0xDA, 0x10, 0xC7, 0xAF 
};

void setup() 
{
  Ethernet.begin(mac,ip);
  Udp.begin(8888);
  Serial.begin(9600);
}


void loop()
{
  int32_t sensorVal = digitalRead(sensorPin);
//  Serial.println(sensorVal);
  OSCMessage msg("/analog/0");
  msg.add((int32_t)sensorVal);
  
  Udp.beginPacket(outIp, outPort);
    msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

  delay(20);
}
