#include <iomanip>
#include <sstream>

#include "CWifiAccessPointData.h"
#include <Arduino.h>

CWifiAccessPointData::CWifiAccessPointData(const std::string &ssid,
                                           wifi_auth_mode_t authType,
                                           int channel, int rssi,
                                           const std::string &bssid)
    : m_Ssid(ssid), m_WifiAuthType(authType), m_Channel(channel), m_RSSI(rssi), m_Bssid(bssid) {

}

// Getters (const methods since they don't modify the object's state)
const std::string &CWifiAccessPointData::GetSsid() const {
   return m_Ssid;
}

wifi_auth_mode_t CWifiAccessPointData::GetAuthMode() const {
  return m_WifiAuthType;
}

int CWifiAccessPointData::GetChannel() const { return m_Channel; }

int CWifiAccessPointData::GetRssi() const { return m_RSSI; }

const std::string &CWifiAccessPointData::GetBssid() const { return m_Bssid; }

std::string CWifiAccessPointData::GetEncryptionTypeString() {
  switch (m_WifiAuthType) {
  case WIFI_AUTH_OPEN:
    return std::string("Open");
  case WIFI_AUTH_WEP:
    return std::string("WEP");
  case WIFI_AUTH_WPA_PSK:
    return std::string("WPA PSK");
  case WIFI_AUTH_WPA2_PSK:
    return std::string("WPA2 PSK");
  case WIFI_AUTH_WPA2_ENTERPRISE:
    return std::string("WPA2 Enterprise");
  case WIFI_AUTH_WPA3_PSK:
    return std::string("WPA2 PSK");
  case WIFI_AUTH_WPA2_WPA3_PSK:
    return std::string("WPA2/WPA3 PSK");
  case WIFI_AUTH_WAPI_PSK:
    return std::string("WPAI PSK");
  case WIFI_AUTH_WPA3_ENT_192:
    return std::string("WPA3 Etnerpise suit 192-bit");
  default:
    return std::string("Unknown");
  }
}

WifiSignalStrength_e CWifiAccessPointData::GetSignalStrength() {
  if (m_RSSI >= -70 && m_RSSI <= -30) {
    return WifiSignalStrength_e::Excellent;
  } else if (m_RSSI >= -80 && m_RSSI <= -71) {
    return WifiSignalStrength_e::Good;
  } else if (m_RSSI >= -90 && m_RSSI <= -81) {
    return WifiSignalStrength_e::Fair;
  } else if (m_RSSI > -90) { // Weak (but not extremely weak)
    return WifiSignalStrength_e::Weak;
  } else if (m_RSSI <= -90) { // rssi <= -90: Extremely weak
    return WifiSignalStrength_e::ExtremelyWeak;
  }
  return WifiSignalStrength_e::NoSignal;
}
