// WiFi credentials
#define WIFI_SSID       "Yen Luu"
#define WIFI_PASSWORD   "quattran@16"

// Azure IoT Hub settings
#define IOT_HUB_HOSTNAME     "gps-sensor-iot-hub.azure-devices.net"
#define IOT_HUB_DEVICE_ID           "gps-sensor"

// SAS token (you can paste a new one each time it expires)
#define IOT_HUB_SAS_TOKEN    "SharedAccessSignature sr=gps-sensor-iot-hub.azure-devices.net%2Fdevices%2Fgps-sensor&sig=uAjmy%2BYFojCijWvBb5%2BZxV0vkivn4UrgEOOpAt7Vz94%3D&se=1746890810"

// CA certificate
extern const char DIGICERT_ROOT_CA[];
