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

bool CWifiScanner::IsAvailable() const { return m_IsDataReady; }

void CWifiScanner::GetWifiAccessPointsInfo(
    WifiAccessPointMap_t &wifAccessPoint) {
  if (IsAvailable()) {
    wifAccessPoint = m_AvailableWifiNetworks;
  } else {
    wifAccessPoint.clear();
  }
}

void CWifiScanner::ScanWiFi() {
  int numNetworks = WiFi.scanNetworks();
  m_IsDataReady = false;

  if (numNetworks == 0) {
    m_AvailableWifiNetworks.clear();
    log_w("No Wi-Fi networks found.");
  } else {
    log_i("Networks found: %d", numNetworks);
    for (int i = 0; i < numNetworks; ++i) {
      m_AvailableWifiNetworks[std::string(WiFi.SSID(i).c_str())] =
          CWifiAccessPointData(std::string(WiFi.SSID(i).c_str()),
                               WiFi.encryptionType(i), WiFi.channel(i),
                               WiFi.RSSI(i), WiFi.BSSIDstr(i).c_str());
      log_i("%d ->  %s", i + 1, WiFi.SSID(i).c_str());
      log_i("\tChannel: %d RSSI: %d", WiFi.channel(i), WiFi.RSSI(i));
      log_i("\tWifi Auth Type: %s",
            m_AvailableWifiNetworks[std::string(WiFi.SSID(i).c_str())]
                .GetEncryptionTypeString()
                .c_str());
      log_i("\tBSSID: %s", WiFi.BSSIDstr(i).c_str());
    }
  }
  m_IsDataReady = true;
}