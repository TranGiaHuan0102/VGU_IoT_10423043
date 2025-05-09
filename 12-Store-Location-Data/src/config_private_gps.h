// WiFi credentials
#define WIFI_SSID       "ChoiSongJun"
#define WIFI_PASSWORD   "qvuw9726"

// Azure IoT Hub settings
#define IOT_HUB_HOSTNAME     "gps-sensor-iot-hub.azure-devices.net"
#define IOT_HUB_DEVICE_ID           "gps-sensor"

// SAS token (you can paste a new one each time it expires)
#define IOT_HUB_SAS_TOKEN    "SharedAccessSignature sr=gps-sensor-iot-hub.azure-devices.net%2Fdevices%2Fgps-sensor&sig=Ut7z6V012kkYQTW%2BVE7gR4rHBG4%2BKsKE3GTRqAn8Sqw%3D&se=1746758177"

// CA certificate
extern const char DIGICERT_ROOT_CA[];
