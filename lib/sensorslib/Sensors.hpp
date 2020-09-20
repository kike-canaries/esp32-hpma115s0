#ifndef Sensors_hpp
#define Sensors_hpp

#include <hpma115S0.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include <sps30.h>
#include <GUIUtils.hpp>

using namespace std;
#include <vector>

/******************************************************************************
* S E T U P  B O A R D   A N D  F I E L D S
* ---------------------
* please select board on platformio.ini file
******************************************************************************/

// HPMA115S0 sensor config
#ifdef WEMOSOLED
#define HPMA_RX 13  // config for Wemos board & TTGO18650
#define HPMA_TX 15  // some old TTGO18650 have HPMA_RX 18 & HPMA_TX 17
#elif HELTEC
#define HPMA_RX 13  // config for Heltec board, ESP32Sboard & ESPDUINO-32
#define HPMA_TX 12  // some old ESP32Sboard have HPMA_RX 27 & HPMA_TX 25
#elif TTGO_TQ
#define HPMA_RX 13  // config for TTGO_TQ board
#define HPMA_TX 18
#else
#define HPMA_RX 17  // config for D1MIN1 board
#define HPMA_TX 16
#endif

#define LED 2

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

#define PMS_RX 13  // config for D1MIN1 board
#define PMS_TX 14
#define PMS_EN 27   // Panasonic enable pin (2N2222A switch to booster module)

#define SENSOR_INTERVAL 1000 * 60 * 3  // 3 minutes => more is better for the battery
#define SENSOR_SAMPLE 1000 * 35        // 30 seconds => less is better for the battery
#define SENSOR_RETRY 1000              // Sensor read retry
// Sensirion SPS30 sensor
#define SP30_COMMS SERIALPORT2 // UART OR I2C


class Sensors
{
    private:


    // Sensirion SPS30 sensor
    uint8_t ret, error_cnt = 0;
    struct sps_values val;

    int scount = 0;
    bool isInitSetup = true;
    int initSetupCount = 0;
    bool dataReady;
    bool isPmsensorEnable = false;

    uint16_t pm1;      // PM1
    uint16_t pm25;     // PM2.5
    uint16_t pm10;     // PM10

    float humi = 0.0;  // % Relative humidity
    float temp = 0.0;  // Temperature (°C)
    float pres = 0.0;  // Pressure
    float alt  = 0.0;
    float gas  = 0.0;

    void getHumidityRead();

    public: 

    void init();
    void loop();
    bool isDataReady();

    uint16_t getPM1();
    uint16_t getPM25();
    uint16_t getPM10();

    float getTemperature();
    float getHumidity();
    float getPressure();
    float getAltitude();
    float getGas();

    String getFormatTemp();
    String getFormatPress();
    String getFormatHum();
    String getFormatGas();
    String getFormatAlt();

    String getStringPM1();
    String getStringPM25();
    String getStringPM10();
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SENSORSHANDLER)
extern Sensors sensors;
#endif

#endif

