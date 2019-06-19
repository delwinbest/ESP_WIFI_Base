
#define OTA
#define CLIENTID "esp_wifi_base"
//#define SERIALDEBUG

// Hostname
const char *myHostname = CLIENTID;

/* Don't set this wifi credentials. They are configurated at runtime and stored on EEPROM */
char ssid[32] = "";
char password[32] = "";

/* Set these to your desired softAP credentials. They are not configurable at runtime */
const char *softAP_ssid = CLIENTID;
const char *softAP_password = "12345678";

// DNS server
const uint8_t DNS_PORT = 53;
