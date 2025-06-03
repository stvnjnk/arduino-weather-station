
#include <RTClib.h>            // Library for Real-Time Clock (RTC)
#include <DHT.h>               // Library for Humidity and Temperature Sensor (DHT)
#include <Adafruit_BMP085.h>   // Library for Pressure Sensor (BMP085)
#include <LiquidCrystal_I2C.h> // Library for LCD Display
#include <Wire.h>              // Library for I2C communications
#include <BH1750.h>            // Library for Digital Light Sensor

// Initialize LCD display with I2C address 0x27 and dimensions 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Sensor objects
Adafruit_BMP085 bmp;
RTC_DS3231 rtc;
BH1750 lightMeter;
DHT dht(3, DHT11);             // DHT sensor at pin 3, using DHT11 model

// Weekday names for displaying purposes
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define and initialize constants and variables
#define DHTPIN 3               // DHT sensor data pin
#define INTERPIN 2             // Interrupt pin for other functionalities

unsigned long startTime;       // Variable to track start time for timing functions
unsigned long endTime;         // Variable to track end time for timing functions

void setup() {
    Serial.begin(9600);        // Initialize serial communication at 9600 bps
    lcd.begin();               // Initialize LCD
    lcd.backlight();           // Turn on the LCD backlight

    // Initialize sensors
    if (!bmp.begin()) {
        Serial.println("Could not find BMP085 or BMP180 sensor!");
        while (1);
    }
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to the compile date & time
    }
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE); // Initialize light sensor
    dht.begin();               // Initialize DHT sensor

    pinMode(INTERPIN, INPUT);  // Set interrupt pin as input
}

// Main loop to read and display sensor data
void loop() {
    // Get current time from RTC
    DateTime now = rtc.now();

    // Display date and time on LCD
    lcd.setCursor(0, 0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(" ");
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    lcd.print(":");
    lcd.print(now.second());

    // Read and display temperature and humidity from DHT sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Temp: ");
        lcd.print(t);
        lcd.print(" C  Humidity: ");
        lcd.print(h);
        lcd.print("%");
    }

    // Read and display pressure from BMP sensor
    lcd.setCursor(0, 2);
    lcd.print("Pressure: ");
    lcd.print(bmp.readPressure());
    lcd.print(" Pa");

    // Read and display light level from BH1750 sensor
    lcd.setCursor(0, 3);
    lcd.print("Light: ");
    lcd.print(lightMeter.readLightLevel());
    lcd.print(" lx");

    delay(1000); // Update readings every second
}
