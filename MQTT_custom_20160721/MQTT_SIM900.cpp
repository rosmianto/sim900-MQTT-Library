#include "MQTT_SIM900.h"

MQTT_SIM900::MQTT_SIM900(uint8_t RX, uint8_t TX) : _modem(RX, TX)
{
}

void MQTT_SIM900::begin(int speed, String username, String username)
{	
	_modem.begin(speed);
	ATCommand("AT", 1000);  // Should be OK.
	ATCommand("AT+CGATT?", 1000);   // Check if GPRS is attached or not.
	ATCommand("AT+CIPSHUT", 1000);  // Reset previous IP session.
	ATCommand("AT+CIPMUX=0", 1000); // Set connection mode to single.
	ATCommand("AT+CSTT=\"" + APN + "\",\"" + username + "\",\"" + password + "\"", 1000);  // Set APN.
	ATCommand("AT+CIICR", 2500);    // Bring up wireless connection.
	ATCommand("AT+CIFSR", 1000);    // Get IP Address.  
}

int MQTT_SIM900::connect(IPAdress ip, uint16_t port)
{
	
}

void MQTT_SIM900::ATCommand(String command, int ms)
{
  String GsmResponse;
  
  start:
  GsmResponse = "";
  _modem.println(command);
  
  delay(ms);
  
  while(_modem.available() > 0)
    GsmResponse += (char)_modem.read();

  if(command.equals("AT+CIFSR") && GsmResponse.indexOf(".") != -1)
    Serial.println(command + " success.");
  else if(command.equals("AT+CIPSEND") && GsmResponse.indexOf(">") != -1)
    Serial.println(command + " success.");
  else if(command.equals("AT+CIPSEND") && GsmResponse.indexOf("ERROR") != -1)
    Serial.println(command + " try AT+CIPSTART.");
  else if((command.indexOf("AT+CIPSTART") != -1) && GsmResponse.indexOf("ALREADY") != -1)
    Serial.println(command + " success, already connected.");
  else
  {
    if(GsmResponse.indexOf("OK") != -1)
      Serial.println(command + " success.");
    else
    {
      Serial.println(command + " trying...");      
      Serial.println(GsmResponse);
      goto start; // Otherwise keep trying...
    }
  }  
}

void MQTT_SIM900::ATSendData(char data[], int ms)
{
  // Variable declaration.
  String GsmResponse;
  int i = 0;
  
  start:
  GsmResponse = "";
  while(data[i] != 0x1A)
  {
//    Serial.print(data[i], HEX); Serial.print(" ");
    _modem.write(data[i++]);
  }
//  Serial.println();
  _modem.write(0x1A); // Send 0x1A to end request.  
  delay(ms);
  
  while(_modem.available() > 0)
    GsmResponse += (char)_modem.read();

  Serial.println("response: " + GsmResponse);
  
  if(GsmResponse.indexOf("OK") != -1)
    Serial.println("Data sent.");
  else
  {
//    Serial.println(" Data sending...");
      Serial.println("Data sent.");
//    goto start; // Otherwise keep trying...
  }
}

uint8_t MQTT_SIM900::SendAndWait(char data[], int timeout)
{
}