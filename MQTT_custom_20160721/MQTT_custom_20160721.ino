#include "MQTT_SIM900.h"


MQTT_SIM900 mqtt(7, 8);

int i;
char c;

void setup() {
  // put your setup code here, to run once:
  mqtt.begin(19200);
  Serial.begin(19200);

  Serial.println("MQTT Client");
  delay(3000);
  mqtt.GPRS_init("internet","","");
  
  mqtt.MQTT_connect("AdjieMQTT", "52.29.27.181", 1883);
//  ATCommand("AT+CIPSTART=\"TCP\",\"www.google.com\",\"80\"", 1000);
}

void loop() {
  int time_msg = millis()/1000;
  mqtt.MQTT_publish("adjieban", "This is a sample sentence.\nAutosend detik " + String(time_msg));
  delay(500);
}

