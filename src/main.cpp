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

void drawWifiSignal(int strength) {
  int x = 10;
  int y = 10;

  // Clear previous signal area
  tft.fillRect(x, y, 40, 40, ST77XX_BLACK); // Clear the area

  int numBars = map(strength, 0, 100, 0, 4); // Map strength to 0-4 bars
  numBars = constrain(numBars, 0, 4);        // Ensure within 0-4 range

  uint16_t color = ST77XX_BLACK; // Default color (shouldn't be seen)

  if (strength < 25) {
    color = ST77XX_RED;
  } else if (strength < 50) {
    color = ST77XX_YELLOW;
  } else if (strength < 75) {
    color = ST77XX_GREEN;
  } else {
    color = ST77XX_BLUE;
  }

  // Draw bars
  for (int i = 0; i < numBars; i++) {
    int barHeight = (i + 1) * 4;
    tft.fillRect(x + i * 10, y + 32 - barHeight, 6, barHeight, color);
  }
  tft.setCursor(x + 45, y + 10);
  tft.fillRect(x + 45, y + 10, 25, 10, ST77XX_BLACK);
  // Display percentage text (optional)
  char text[4];
  sprintf(text, "%d%%", strength);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2); // Adjust text size as needed
  tft.setCursor(x + 45, y + 10);
  tft.print(text);
}

void setup(void) {
  Serial.begin(115200);
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

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);

  Serial.println("done");
}

void loop() {
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println("Scanning for Wifi networks...");
  wifiScanner.ScanWiFi();
  // Simulate changing signal strength (replace with actual readings)
  for (int strength = 0; strength <= 100; strength += 20) {
    drawWifiSignal(strength);
    delay(1000);
  }

}