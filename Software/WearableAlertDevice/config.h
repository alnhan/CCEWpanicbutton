/*
* Configuration settings for the Wearable Alert Device.
* Note: GPIO numbers are used, not pin numbers.
*
* @author Alex Ho
* @2026 University of Oklahoma
*/

#define BUTTON 17

// ----------------------------------
// I2C AND GPS MODULE SETTINGS
// ----------------------------------
// #define I2C_SDA 11
// #define I2C_SCL 12

// Real-Time Clock Register
// #define I2C_SECOND_ADDR 0x00
// #define I2C_MINUTE_ADDR 0x01
// #define I2C_HOUR_ADDR 0x02
// #define I2C_WEEK_ADDR 0x03
// #define I2C_DAY_ADDR 0x04
// #define I2C_MONTH_ADDR 0x05
// #define I2C_YEAR_ADDR 0x06
#define INITIAL_YEAR 2026
#define INITIAL_MONTH 3
#define INITIAL_DAY 14
#define INITIAL_HOUR 0
#define INITIAL_MINUTE 0
#define INITIAL_SECOND 0

// ----------------------------------
// I2S AND MIC SETTINGS
// ----------------------------------
// Note: Using standard mode for I2S
#define I2S_WS 8
#define I2S_SEL 7
#define I2S_SCK 6
#define I2S_DO 5
#define MIC_LEFT_CH 0
#define MIC_RIGHT_CH 1
#define MIC_SAMPLING_RATE 44100

// Bluetooth
#define SERVICE_UUID "3098A182-02B0-4A35-889A-93B71E1748B9"
#define CHARACTERISTIC_UUID "B536BCCE-2C24-4F7C-BF9F-1DE558316263"
#define BLE_SERVER_NAME "Wearable_Alert_Device"
#define MTU_SIZE 23
