#include "NetworkModule.h"

#if defined(KNX_IP_W5500)
Wiznet5500lwIP EthernetlwIP(PIN_ETH_SS, ETH_SPI_INTERFACE);
#else
    #error "no Ethernet stack specified, #define KNX_IP_WIFI or KNX_IP_W5500"
#endif

const char* www_username = "admin";
const char* www_password = "picow";

WebServer HttpServer;
HTTPUpdateServer HttpUpdater;

const std::string NetworkModule::name()
{
    return "NetworkModule";
}

const std::string NetworkModule::version()
{
    return MODULE_Network_Version;
}

void NetworkModule::init()
{
    logInfoP("Initalize network hardware");
    ETH_SPI_INTERFACE.setRX(PIN_ETH_MISO);
    ETH_SPI_INTERFACE.setTX(PIN_ETH_MOSI);
    ETH_SPI_INTERFACE.setSCK(PIN_ETH_SCK);
    ETH_SPI_INTERFACE.setCS(PIN_ETH_SS);

    //    EthernetlwIP.setSPISpeed(30000000);
    //    lwipPollingPeriod(10);
}

void NetworkModule::setup(bool configured)
{
    openknx.info2Led.activity(_activity, true);
    // HttpServer.on("/", []() -> void {
    //     if (!HttpServer.authenticate(www_username, www_password))
    //     {
    //         return HttpServer.requestAuthentication();
    //     }
    //     HttpServer.send(200, "text/plain", "Login OK");
    // });

    initInterface();
    HttpUpdater.setup(&HttpServer);
    HttpServer.begin();
    MDNS.addService("http", "tcp", 80);
}

void NetworkModule::initInterface()
{
    logInfoP("Initalize network interface");
    logIndentUp();

    const char* hostname = "OpenKNX";

    logInfoP("Hostname: %s", hostname);
    EthernetlwIP.hostname((hostname));

    IPAddress localIP(192, 168, 13, 217);
    IPAddress netmask(255, 255, 255, 0);
    IPAddress gateway(192, 168, 13, 254);
    IPAddress dns1(192, 168, 13, 254);
    IPAddress dns2(192, 168, 13, 254);

    if (!EthernetlwIP.config(localIP, gateway, netmask, dns1, dns2))
    {
        openknx.hardware.fatalError(7, "Network: Invalid network settings");
    }

    logInfoP("Address: %s", localIP.toString().c_str());
    logInfoP("Netmask: %s", netmask.toString().c_str());
    logInfoP("Gateway: %s", gateway.toString().c_str());
    logInfoP("Gateway: %s", gateway.toString().c_str());
    logInfoP("Nameserver1: %s", dns1.toString().c_str());
    logInfoP("Nameserver1: %s", dns2.toString().c_str());

    if (!EthernetlwIP.begin())
    {
        openknx.hardware.fatalError(7, "Network: Error communicating with W5500 Ethernet chip");
    }

    logInfoP("Link: %i", EthernetlwIP.isLinked());

    logIndentDown();

    MDNS.begin(hostname);
}

void NetworkModule::initTFTPServer()
{

    // tftp_context;
    // tftp_init(tftp_context);
}

void NetworkModule::loop(bool configured)
{
    // if (delayCheck(_lastLinkCheck, 2000))
    // {
    //     _lastLinkCheck = millis();
    //     bool status = EthernetlwIP.isLinked();
    //     if (_lastLinkStatus != status)
    //     {
    //         if (status)
    //         {
    //             logInfoP("Connection established");
    //             openknx.info2Led.activity(_activity, true);
    //             _lastLinkStatus = true;
    //         }
    //         else
    //         {

    //             logInfoP("Connection disconnected");
    //             openknx.info2Led.off();
    //             _lastLinkStatus = false;
    //         }
    //     }
    // }

    HttpServer.handleClient();
    MDNS.update();
}

void NetworkModule::showInformations()
{
    openknx.logger.logWithPrefixAndValues("IP-Address", "%s", EthernetlwIP.localIP().toString().c_str());
}
NetworkModule openknxNetworkModule;