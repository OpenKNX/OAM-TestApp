#pragma once
#include "OpenKNX.h"

#ifdef KNX_IP_W5500
    #include <W5500lwIP.h>
#endif

#include <WebServer.h>
#include <HTTPUpdateServer.h>
#include <LEAmDNS.h>
#include <WebServer.h>
// #include <LwipIntfDev.h>
// #include <utility/w5500.h>
// #include <LwipEthernet.h>
// #include <WiFi.h>

// #ifndef NETWORK_MODULE_H
//     #define NETWORK_MODULE_H

// #endif

class NetworkModule : public OpenKNX::Module
{
  public:
    NetworkModule() {
      //_httpServer = new WebServer(80);
    }
    const std::string name() override;
    const std::string version() override;
    void init() override;
    void loop(bool configured) override;
    void setup(bool configured) override;
    void showInformations() override;
    void initInterface();
    void initTFTPServer();

  private:

    uint32_t _activity = 0;
    uint32_t _lastLinkCheck = 0;
    bool _lastLinkStatus = false;
};

extern NetworkModule openknxNetworkModule;