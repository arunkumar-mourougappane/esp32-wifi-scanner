/**
 * @file main.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief This is an application to scan WiFi and print to
 *        to user interface.
 * @version 0.1
 * @date 2025-02-15
 *
 * Copyright (c) Arunkumar Mourougappane
 *
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Arduino.h>
#include <WiFi.h>

#include "CWifiScanner.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
CWifiScanner wifiScanner;
static uint_least16_t LARGE_TEXT_CHAR_COUNT = 0;
static uint_least16_t MEDIUM_TEXT_CHAR_COUNT = 0;
static uint_least16_t SMALL_TEXT_CHAR_COUNT = 0;
static uint_least16_t XSMALL_TEXT_CHAR_COUNT = 0;

static uint_least16_t LARGE_TEXT_LINE_COUNT = 0;
static uint_least16_t MEDIUM_TEXT_LINE_COUNT = 0;
static uint_least16_t SMALL_TEXT_LINE_COUNT = 0;
static uint_least16_t XSMALL_TEXT_LINE_COUNT = 0;

void drawWifiSignal(int16_t x, int16_t y, WifiSignalStrength_e strength) {

  // Clear previous signal area
  tft.fillRect(x, y, 16, 14, ST77XX_BLACK); // Clear the area

  int numBars = map(strength, 0, 5, 0, 4); // Map strength to 0-4 bars
  numBars = constrain(numBars, 0, 4);        // Ensure within 0-4 range

  uint16_t color = ST77XX_BLACK; // Default color (shouldn't be seen)

  switch (strength) {
  case WifiSignalStrength_e::ExtremelyWeak:
    color = ST77XX_RED;
    break;
  case WifiSignalStrength_e::Weak:
    color = ST77XX_ORANGE;
    break;
  case WifiSignalStrength_e::Fair:
    color = ST77XX_YELLOW;
    break;
  case WifiSignalStrength_e::Good:
    color = ST77XX_GREEN;
    break;
  case WifiSignalStrength_e::Excellent:
    color = ST77XX_BLUE;
    break;
  case WifiSignalStrength_e::NoSignal:
  default:
    color = ST77XX_BLACK;
    break;
  }

  // Draw bars
  for (int i = 0; i < numBars; i++) {
    int barHeight = (i + 1) * 2.5;
    tft.fillRect(x + i * 4, y + 10 - barHeight, 3, barHeight, color);
  }

}

void setup(void) {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println();
  delay(3000);
  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  Serial.println(F("Initialized"));
  log_i("TFT width: %d", tft.width());
  log_i("TFT height: %d", tft.height());
  tft.setRotation(3);

  const char *text = "I";
  int16_t x = 0;  // X coordinate of the text
  int16_t y = 20; // Y coordinate of the text
  int16_t x1, y1;
  uint16_t w, h; // Variables to store the bounds
  log_i("Getting line count for small text");
  tft.setTextSize(1);
  tft.setCursor(88,(tft.height()/2) - 8);
  tft.println("Initializing");
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h);
  log_i("Total Sentence width: %d", w);
  log_i("Total Sentence height: %d", h);
  XSMALL_TEXT_LINE_COUNT = tft.height() / h;
  XSMALL_TEXT_CHAR_COUNT = tft.width() / w;

  log_i("Getting line count for small text");
  tft.setTextSize(2);
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h);
  log_i("Total Sentence width: %d", w);
  log_i("Total Sentence height: %d", h);
  SMALL_TEXT_LINE_COUNT = tft.height() / h;
  SMALL_TEXT_CHAR_COUNT = tft.width() / w;

  log_i("Getting line count for medium text");
  tft.setTextSize(3);
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h);
  log_i("Total Sentence width: %d", w);
  log_i("Total Sentence height: %d", h);
  MEDIUM_TEXT_LINE_COUNT = tft.height() / h;
  MEDIUM_TEXT_CHAR_COUNT = tft.width() / w;

  log_i("Getting line count for large text");
  tft.setTextSize(4);
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h);
  log_i("Total Sentence width: %d", w);
  log_i("Total Sentence height: %d", h);
  LARGE_TEXT_LINE_COUNT = tft.height() / h;
  LARGE_TEXT_CHAR_COUNT = tft.width() / w;

  log_i("X-Small Text Line Count: %d", XSMALL_TEXT_LINE_COUNT);
  log_i("Small Text Line Count: %d", SMALL_TEXT_LINE_COUNT);
  log_i("Medium Text Line Count: %d", MEDIUM_TEXT_LINE_COUNT);
  log_i("Large Text Line Count: %d", LARGE_TEXT_LINE_COUNT);
  delay(1200);
  tft.setTextSize(1);
  tft.setCursor(x, y);
  tft.fillScreen(ST77XX_BLACK);
  log_i("Initialization Complete.");
  tft.setCursor(57,(tft.height()/2) - 8);
  tft.println("Initialization Complete!");
#if 0
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  int16_t y_cordinate = 0;
  for (int i =0; i < tft.height(); i=i+(tft.height()/MEDIUM_TEXT_LINE_COUNT))
  {
    tft.setCursor(0,y_cordinate);
    tft.printf("Hello, World! %d", i/(tft.height()/MEDIUM_TEXT_LINE_COUNT));
    y_cordinate+=(tft.height()/MEDIUM_TEXT_LINE_COUNT);
    delay(1000);
  }

#endif
  delay(1000);
  Serial.println("done");
}

void loop() {
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  log_i("Scanning for Wifi networks...");
  wifiScanner.ScanWiFi();

  if (wifiScanner.IsAvailable()) {
    WifiAccessPointMap_t wifiAccessPoints;
    wifiScanner.GetWifiAccessPointsInfo(wifiAccessPoints);
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    int16_t y_co = 0;
    int16_t char_width = tft.width() / SMALL_TEXT_CHAR_COUNT;
    for (std::unordered_map<std::string, CWifiAccessPointData>::const_iterator
             it = wifiAccessPoints.begin();
         it != wifiAccessPoints.end(); ++it) {
      std::string ssid = it->second.GetSsid().substr(0, 17);
      WifiSignalStrength_e signalStrength = it->second.GetSignalStrength();
      log_i("SSID: %s\tRSSI: %d", it->second.GetSsid().c_str(), it->second.GetSignalStrength());
      tft.print(ssid.c_str());
      tft.setCursor(ssid.length()*char_width + 5, y_co);
      drawWifiSignal(200, y_co, signalStrength);
      y_co = y_co + (tft.height() / SMALL_TEXT_LINE_COUNT);
      if (y_co + 10 > tft.height()) {
        delay(2000);
        tft.fillScreen(ST77XX_BLACK);
        y_co = 0;
      }
      tft.setCursor(0, y_co);
    }
    log_i("Number of Networks Found: %zu", wifiAccessPoints.size());
  }
}