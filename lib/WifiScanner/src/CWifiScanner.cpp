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
#include <string>

void CWifiScanner::ScanWiFi() {
  int numNetworks = WiFi.scanNetworks();
  m_IsDataReady = false;

  if (numNetworks == 0) {
    m_AvailableWifiNetworks.clear();
    m_IsDataReady = true;
    Serial.println("No Wi-Fi networks found.");
  } else {
    Serial.printf("Networks found: %d\n", numNetworks);
    Serial.println(" Wi-Fi networks found:");
    Serial.printf("%3d|%-30s|%10s|%10d|%-25s\n", "No", "SSID", "RSSI(dBm)",
                  "Channel", "BSSID");
    for (int i = 0; i < numNetworks; ++i) {
         CWifiAccessPointData wifiAccessPoint(std::string(WiFi.SSID(i).c_str()), WiFi.encryptionType(i), WiFi.channel(i), WiFi.RSSI(i), WiFi.BSSID(i));
         m_AvailableWifiNetworks[std::string(WiFi.SSID(i).c_str())] = wifiAccessPoint;
         Serial.printf("%3d|%-30s|%10d|%10d|%-25s\n", i+1, wifiAccessPoint.GetSsid().c_str(), wifiAccessPoint.GetSignalStrength(), wifiAccessPoint.GetSignalStrength(), wifiAccessPoint.GetChannel(), wifiAccessPoint.GetBssid().c_str());
    }
  }
}