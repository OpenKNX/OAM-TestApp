#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "VirtualButtonModule.h"

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

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxDummyModule);
#ifndef ARDUINO_ARCH_SAMD
    openknx.addModule(3, openknxVirtualButtonModule);
#endif

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
        openknx.info1Led.on(func1test);
    #endif
    });
    openknx.func1Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func1 button double click");
    #ifdef INFO1_LED_PIN
        openknx.info1Led.pulsing();
    #endif
    });
    openknx.func1Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func1 button long click");
    #ifdef INFO1_LED_PIN
        openknx.info1Led.blinking();
    #endif
    });
#endif
#ifdef FUNC2_BUTTON_PIN
    openknx.func2Button.onShortClick([]() -> void {
        func2test = !func2test;
        logInfo("ButtonTest", "Func2 button short click");
    #ifdef INFO2_LED_PIN
        openknx.info2Led.on(func2test);
    #endif
    });
    openknx.func2Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func2 button double click");
    #ifdef INFO2_LED_PIN
        openknx.info2Led.pulsing();
    #endif
    });
    openknx.func2Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func2 button long click");
    #ifdef INFO2_LED_PIN
        openknx.info2Led.blinking();
    #endif
    });
#endif
#ifdef FUNC3_BUTTON_PIN
    openknx.func3Button.onShortClick([]() -> void {
        func3test = !func3test;
        logInfo("ButtonTest", "Func3 button short click");
    #ifdef INFO3_LED_PIN
        openknx.info3Led.on(func3test);
    #endif
    });
    openknx.func3Button.onDoubleClick([]() -> void {
        logInfo("ButtonTest", "Func3 button double click");
    #ifdef INFO3_LED_PIN
        openknx.info3Led.pulsing();
    #endif
    });
    openknx.func3Button.onLongClick([]() -> void {
        logInfo("ButtonTest", "Func3 button long click");
    #ifdef INFO3_LED_PIN
        openknx.info3Led.blinking();
    #endif
    });
#endif

    // openknx.progLed.off();
    // openknx.progLed.on();
    // openknx.progLed.blinking();
    // openknx.progLed.pulsing();
    // openknx.progLed.brightness(60);

#ifdef INFO1_LED_PIN
    openknx.info1Led.pulsing();
// openknx.info1Led.brightness(60);
#endif
#ifdef INFO2_LED_PIN
    openknx.info2Led.pulsing();
// openknx.info2Led.brightness(60);
#endif
#ifdef INFO3_LED_PIN
    openknx.info3Led.pulsing();
// openknx.info3Led.brightness(60);
#endif
    // openknx.timerInterrupt.interrupt();
    // #ifdef FORCE_ACK
    //     knx.bau().getDataLinkLayer()->forceAck(true);
    // #endif
}

#ifdef OKNXHW_REG1_BASE_V1
#endif

void loop()
{
    openknx.loop();
    if (delayCheck(_debugCore0, 1000))
    {
        //  #if MASK_VERSION == 0x07B0
        //          TpUartDataLinkLayer *dll = knx.bau().getDataLinkLayer();
        //  #endif
        //  #if defined(ARDUINO_ARCH_RP2040) && defined(USE_TP_RX_QUEUE)
        //          if (false)
        //          {
        //              uint32_t start = millis();
        //              logInfo("Erase", "Start");
        //              logIndentUp();
        //              for (size_t i = 0x00090000; i <= 0x0009F000; i += 0x1000)
        //              {
        //                  logInfo("Erase", "Block: %04X", i);
        //                  noInterrupts();
        //                  rp2040.idleOtherCore();
        //                  flash_range_erase(i, 0x01000);
        //                  rp2040.resumeOtherCore();
        //                  interrupts();
        //                  dll->processRxISR();
        //              }
        //              logIndentDown();
        //              logInfo("Erase", "End %ims", (millis() - start));
        //          }
        //  #endif

        // #if MASK_VERSION == 0x07B0
        //         logInfo("KNX", "Connected: %i - ProcessedFrames: %i - IgnoredFrames: %i - InvalidFrames: %i - UnknownControl: %i",
        //                 dll->enabled(), dll->getRxProcessdFrameCounter(), dll->getRxIgnoredFrameCounter(), dll->getRxInvalidFrameCounter(), dll->getRxUnknownControlCounter());
        // #endif

        // openknx.console.showMemory();
        // logInfo("-", "-");
        _debugCore0 = millis();
    }
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