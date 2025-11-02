#include "DummyModule.h"
#include "HardwareConfig.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "VirtualButtonModule.h"
#include "StatusLEDModule.h"
// #include <async_http_client.h>

#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
    #ifndef OPENKNX_USB_EXCHANGE_IGNORE
        #include "UsbExchangeModule.h"
    #endif
    #if defined(KNX_IP_LAN) || defined(KNX_IP_WIFI)
        #include "NetworkModule.h"
    #endif
#endif

#ifdef ARDUINO_ARCH_ESP32
    #if defined(KNX_IP_LAN) || defined(KNX_IP_WIFI)
        #include "NetworkModule.h"
    #endif

#endif

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;

bool func1test = false;
bool func2test = false;
bool func3test = false;
bool core1_separate_stack = true;

// AsyncHTTPClient http;
// #include "SPI.h"
// #include <ELECHOUSE_CC1101_SRC_DRV.h>

void setup()
{
#ifdef OPENKNX_LED_NO_AUTOCONF
    #ifdef LED_AUTODETECT

        // delay(3000);
        // while(true)
        // {
        //     pinMode(6, INPUT);
        //     Serial.printf("Pin 6 state mode INPUT %d\n", digitalRead(6));
        //     pinMode(6, INPUT_PULLUP);
        //     Serial.printf("Pin 6 state mode INPUT_PULLUP %d\n", digitalRead(6));
        //     pinMode(6, INPUT_PULLDOWN);
        //     Serial.printf("Pin 6 state mode INPUT_PULLDOWN %d\n", digitalRead(6));

        //     pinMode(22, INPUT);
        //     Serial.printf("Pin 22 state mode INPUT %d\n", digitalRead(22));
        //     pinMode(22, INPUT_PULLUP);
        //     Serial.printf("Pin 22 state mode INPUT_PULLUP %d\n", digitalRead(22));
        //     pinMode(22, INPUT_PULLDOWN);
        //     Serial.printf("Pin 22 state mode INPUT_PULLDOWN %d\n", digitalRead(22));

        //     Serial.println("Done, please restart");
        //     delay(2000);
        // }

        pinMode(22, INPUT);
        if(digitalRead(22))
        {
            openknx.leds.addLed(new OpenKNX::Led::Serial(0, PROG_LED_PIN, 30, 0, 0), OpenKNX::Led::LED_TYPE_PROG);
            openknx.leds.addLed(new OpenKNX::Led::Serial(1, PROG_LED_PIN, 20, 0, 20), OpenKNX::Led::LED_TYPE_INFO1);
            openknx.leds.addLed(new OpenKNX::Led::Serial(2, PROG_LED_PIN, 0, 20, 20), OpenKNX::Led::LED_TYPE_INFO2);
            openknx.leds.addLed(new OpenKNX::Led::Serial(3, PROG_LED_PIN, 20, 20, 0), OpenKNX::Led::LED_TYPE_INFO3);
        }
        else
        {
            openknx.leds.addLed(new OpenKNX::Led::GPIO(PROG_LED_PIN, PROG_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_PROG);
            openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO1_LED_PIN, INFO1_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO1);
            openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO2_LED_PIN, INFO2_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO2);
            openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO3_LED_PIN, INFO3_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO3);
        }
    #else
        #ifdef OPENKNX_SERIALLED_ENABLE
        openknx.leds.addLed(new OpenKNX::Led::Serial(PROG_LED_PIN, OPENKNX_SERIALLED_PIN, 30, 30, 30), OpenKNX::Led::LED_TYPE_PROG);
        openknx.leds.addLed(new OpenKNX::Led::Serial(INFO1_LED_PIN, OPENKNX_SERIALLED_PIN, 30, 30, 30), OpenKNX::Led::LED_TYPE_INFO1);
        openknx.leds.addLed(new OpenKNX::Led::Serial(INFO2_LED_PIN, OPENKNX_SERIALLED_PIN, 30, 30, 30), OpenKNX::Led::LED_TYPE_INFO2);
        openknx.leds.addLed(new OpenKNX::Led::Serial(INFO3_LED_PIN, OPENKNX_SERIALLED_PIN, 30, 30, 30), OpenKNX::Led::LED_TYPE_INFO3);
        #else
        openknx.leds.addLed(new OpenKNX::Led::GPIO(PROG_LED_PIN, PROG_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_PROG);
        openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO1_LED_PIN, INFO1_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO1);
        openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO2_LED_PIN, INFO2_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO2);
        openknx.leds.addLed(new OpenKNX::Led::GPIO(INFO3_LED_PIN, INFO3_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_INFO3);
        openknx.leds.addLed(new OpenKNX::Led::GPIO(28, HIGH), OpenKNX::Led::LED_TYPE_USER);
        #endif
    #endif
#endif


    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);

    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxDummyModule);
    #ifndef ARDUINO_ARCH_SAMD
        openknx.addModule(3, openknxVirtualButtonModule);
    #endif
    openknx.addModule(4, openknxStatusLEDModule);

#if defined(KNX_IP_LAN) || defined(KNX_IP_WIFI)
    openknx.addModule(7, openknxNetwork);
#endif

#ifdef ARDUINO_ARCH_RP2040
    #ifndef OPENKNX_USB_EXCHANGE_IGNORE
    openknx.addModule(8, openknxUsbExchangeModule);
    #endif
    openknx.addModule(9, openknxFileTransferModule);
#endif

    openknx.setup();
#ifdef FUNC1_BUTTON_PIN
    openknx.func1Button.onShortClick([]() -> void {
        func1test = !func1test;
        logInfo("ButtonTest", "Func1 button short click");
    #ifdef INFO1_LED_PIN
        openknx.leds.getLed(10)->on(func1test);
    #endif
    });
    openknx.func1Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func1 button double click");
    #ifdef INFO1_LED_PIN
        openknx.leds.getLed(10)->pulsing();
    #endif
    });
    openknx.func1Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func1 button long click");
    #ifdef INFO1_LED_PIN
        openknx.leds.getLed(10)->blinking();
    #endif
    });
#endif
/*
#ifdef FUNC2_BUTTON_PIN
    openknx.func2Button.onShortClick([]() -> void {
        func2test = !func2test;
        logInfo("ButtonTest", "Func2 button short click");
    #ifdef INFO2_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2)->on(func2test);
    #endif
    });
    openknx.func2Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func2 button double click");
    #ifdef INFO2_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2)->pulsing();
    #endif
    });
    openknx.func2Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func2 button long click");
    #ifdef INFO2_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2)->blinking();
    #endif
    });
#endif
#ifdef FUNC3_BUTTON_PIN
    openknx.func3Button.onShortClick([]() -> void {
        func3test = !func3test;
        logInfo("ButtonTest", "Func3 button short click");
    #ifdef INFO3_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3)->on(func3test);
    #endif
    });
    openknx.func3Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func3 button double click");
    #ifdef INFO3_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3)->pulsing();
    #endif
    });
    openknx.func3Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func3 button long click");
    #ifdef INFO3_LED_PIN
        openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3)->blinking();
    #endif
    });
#endif
*/

#ifdef INFO1_LED_PIN
    //openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO1)->on();
// openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO1)->brightness(60);
#endif
#ifdef INFO2_LED_PIN
    //openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2)->on();
// openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2)->brightness(60);
#endif
#ifdef INFO3_LED_PIN
    //openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3)->on();
// openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3)->brightness(60);
#endif



}

void loop()
{
    if (delayCheck(_debugCore0, 10000))
    {
        _debugCore0 = millis();
    }

    openknx.loop();
    // delay(50);
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
    _debugCore1 = millis();
}
#endif