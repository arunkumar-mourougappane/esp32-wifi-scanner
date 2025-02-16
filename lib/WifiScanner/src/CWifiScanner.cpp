/**
 * @file CWifiScanner.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Implementation for wrappers around Arduino Wifi API
 *        to scan Wi-Fi AP Data.
 * @version 0.1
 * @date 2025-02-15
 *
 * Copyright (c) Arunkumar Mourougappane
 *
 */
#include "CWifiScanner.h"
#include <atomic>
#include <iomanip>
#include <sstream>
#include <string>

void CWifiScanner::ScanWiFi() {
  int numNetworks = WiFi.scanNetworks();
  m_IsDataReady = false;

  if (numNetworks == 0) {
    m_AvailableWifiNetworks.clear();
    Serial.println("No Wi-Fi networks found.");
  } else {
    Serial.printf("Networks found: %d\n", numNetworks);
    Serial.println(" Wi-Fi networks found:");

    for (int i = 0; i < numNetworks; ++i) {
      m_AvailableWifiNetworks[std::string(WiFi.SSID(i).c_str())] =
          CWifiAccessPointData(std::string(WiFi.SSID(i).c_str()),
                               WiFi.encryptionType(i), WiFi.channel(i),
                               WiFi.RSSI(i), WiFi.BSSIDstr(i).c_str());
      Serial.printf("%d ->  %s\n",i+1, WiFi.SSID(i).c_str());
      Serial.printf("\tChanel: %d RSSI: %d\n",WiFi.channel(i), WiFi.RSSI(i));
      Serial.printf("\tWifi Auth Type: %s\n",m_AvailableWifiNetworks[std::string(WiFi.SSID(i).c_str())].GetEncryptionTypeString().c_str());
      Serial.printf("\tBSSID: %s\n", WiFi.BSSIDstr(i).c_str());
    }
  }
  m_IsDataReady = true;
}