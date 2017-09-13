#ifndef MQTT_SIM900_H
#define MQTT_SIM900_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class MQTT_SIM900 : Client
{
	public:
		MQTT_SIM900(uint8_t RX, uint8_t TX);
		void MQTT_SIM900::begin(int speed, String username, String username);
	
	private:
		SoftwareSerial _modem;
		void ATCommand(String command, int ms);
		void ATSendData(char data[], int ms);
		uint8_t MQTT_SIM900::SendAndWait(char data[], int timeout);
};
#endif