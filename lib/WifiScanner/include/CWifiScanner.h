/**
 * @file CWifiScanner.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Header file containing the definitions for API
 *        to perform wifi scanning.
 * @version 1.0.0
 * @date 2025-02-15
 *
 * Copyright (c) Arunkumar Mourougappane
 *
 */

#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <atomic>
#include <iostream>
#include <string>
#include <unordered_map>

#include <Arduino.h>
#include <WiFi.h>

#include "CWifiAccessPointData.h"

typedef std::unordered_map<std::string, CWifiAccessPointData>
    WifiAccessPointMap_t;

class CWifiScanner {

private:
  std::atomic<bool> m_IsDataReady;
  WifiAccessPointMap_t m_AvailableWifiNetworks;

public:
  CWifiScanner() {};
  bool IsAvailable() const;
  void GetWifiAccessPointsInfo(WifiAccessPointMap_t &wifAccessPoint);
  void ScanWiFi();
};

#endif // !WIFI_SCANNER_H
