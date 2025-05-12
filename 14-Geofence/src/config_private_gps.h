// WiFi credentials
#define WIFI_SSID       "ChoiSongJun"
#define WIFI_PASSWORD   "qvuw9726"

// Azure IoT Hub settings
#define IOT_HUB_HOSTNAME     "gps-sensor-iot-hub.azure-devices.net"
#define IOT_HUB_DEVICE_ID           "gps-sensor"

// SAS token (you can paste a new one each time it expires)
#define IOT_HUB_SAS_TOKEN    "SharedAccessSignature sr=gps-sensor-iot-hub.azure-devices.net%2Fdevices%2Fgps-sensor&sig=b7rQuD100imhp5a5pGFPX1LYrIwtpyEwh4Krkd1KD1s%3D&se=1747035700"

// CA certificate
extern const char DIGICERT_ROOT_CA[];
