#include <EEPROM.h>
/** Load WLAN credentials from EEPROM */
void loadCredentials(char* ssid, char* password) {
  EEPROM.begin(512);
  EEPROM.get(0, ssid);
  EEPROM.get(0 + sizeof(ssid), password);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.end();
  if (strcmp(ok,"OK") != 0) {
    ssid[0] = 0;
    password[0] = 0;
  }
  if (strlen(ssid) > 0) {
  } else {
  }
}

/** Store WLAN credentials to EEPROM */
void saveCredentials(char *ssid, char *password) {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0 + sizeof(ssid), password);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}
