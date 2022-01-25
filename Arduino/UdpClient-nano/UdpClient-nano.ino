#include <UIPEthernet.h>

EthernetUDP udp;
unsigned long next;
static int sensorPin = 5;


void setup() {
  Serial.begin(9600);
  uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x07};
  Ethernet.begin(mac, IPAddress(23, 0, 0, 4));
  next = millis() + 10;
}

void loop() {
  int sensorVal = digitalRead(sensorPin);
  Serial.println(sensorVal);
  char message[] = "3 ";

  if (sensorVal == 1) {
    strcat(message, "on");
  }
  else if (sensorVal == 0) {
    strcat(message, "off");
  }

  udp.beginPacket(IPAddress(23, 0, 0, 1), 2323);
  udp.write(message);
  udp.endPacket();
  delay(10);
}
