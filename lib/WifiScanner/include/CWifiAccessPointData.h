/**
 * @file CWifiAccessPointData.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Structure to hold Wifi Access Point information.
 * @version 0.1
 * @date 2025-02-15
 *
 * Copyright (c) Arunkumar Mourougappane
 *
 */

#ifndef WIFI_ACCESSPOINT_DATA_H
#define WIFI_ACCESSPOINT_DATA_H

#include <WiFi.h>
#include <string>

typedef enum {
  NoSignal,
  ExtremelyWeak,
  Weak,
  Fair,
  Good,
  Excellent
} WifiSignalStrength_e;

class CWifiAccessPointData {
private:
  std::string m_Ssid;
  wifi_auth_mode_t m_WifiAuthType;
  int m_Channel;
  std::string m_Bssid;
  int m_RSSI;

public:
  CWifiAccessPointData(const std::string &ssid, wifi_auth_mode_t authType,
                       int channel, int rssi, const std::string &bssid);
   CWifiAccessPointData() {};
  // Getters (const methods since they don't modify the object's state)
  const std::string &GetSsid() const;

  wifi_auth_mode_t GetAuthMode() const;

  int GetChannel() const;

  int GetRssi() const;

  const std::string &GetBssid() const;

  WifiSignalStrength_e GetSignalStrength();

  std::string GetEncryptionTypeString();
};
#endif // !WIFI_ACCESSPOINT_DATA_H