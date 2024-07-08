#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "VirtualButtonModule.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
    #include "UsbExchangeModule.h"
    #if defined(KNX_IP_W5500) || defined(KNX_IP_GENERIC) || defined(KNX_IP_WIFI)
        #include "NetworkModule.h"
    #endif
#endif

#ifdef ARDUINO_ARCH_ESP32
    #include "NetworkModule.h"
#endif

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;

bool func1test = false;
bool func1test2 = false;
bool core1_separate_stack = true;

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxDummyModule);
    openknx.addModule(3, openknxVirtualButtonModule);
#ifdef ARDUINO_ARCH_RP2040
    #if defined(KNX_IP_W5500) || defined(KNX_IP_GENERIC) || defined(KNX_IP_WIFI)
    openknx.addModule(7, openknxNetwork);
    #endif
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);
#endif
#ifdef ARDUINO_ARCH_ESP32
    openknx.addModule(7, openknxNetwork);
#endif
    openknx.setup();

#ifdef FUNC1_BUTTON_PIN
    openknx.func1Button.onShortClick([]() -> void {
        func1test = !func1test;
        openknx.info2Led.on(func1test);
        openknx.info3Led.on(!func1test);
    });
    openknx.func1Button.onDoubleClick([]() -> void {
        openknx.info2Led.on(false);
        openknx.info3Led.on(false);
    });
    openknx.func1Button.onLongClick([]() -> void {
        func1test2 = !func1test2;
        openknx.info1Led.on(func1test2);
    });
#endif

    // openknx.progLed.off();
    // openknx.progLed.on();
    // openknx.progLed.blinking();
    // openknx.progLed.pulsing();

    // #ifdef FORCE_ACK
    //     knx.bau().getDataLinkLayer()->forceAck(true);
    // #endif
}

void loop()
{
    openknx.loop();
    if (delayCheck(_debugCore0, 60000))
    {
        // #if MASK_VERSION == 0x07B0
        //         TpUartDataLinkLayer *dll = knx.bau().getDataLinkLayer();
        // #endif
        // #if defined(ARDUINO_ARCH_RP2040) && defined(USE_TP_RX_QUEUE)
        //         if (false)
        //         {
        //             uint32_t start = millis();
        //             logInfo("Erase", "Start");
        //             logIndentUp();
        //             for (size_t i = 0x00090000; i <= 0x0009F000; i += 0x1000)
        //             {
        //                 logInfo("Erase", "Block: %04X", i);
        //                 noInterrupts();
        //                 rp2040.idleOtherCore();
        //                 flash_range_erase(i, 0x01000);
        //                 rp2040.resumeOtherCore();
        //                 interrupts();
        //                 dll->processRxISR();
        //             }
        //             logIndentDown();
        //             logInfo("Erase", "End %ims", (millis() - start));
        //         }
        // #endif

        // #if MASK_VERSION == 0x07B0
        //         logInfo("KNX", "Connected: %i - ProcessedFrames: %i - IgnoredFrames: %i - InvalidFrames: %i - UnknownControl: %i",
        //                 dll->enabled(), dll->getRxProcessdFrameCounter(), dll->getRxIgnoredFrameCounter(), dll->getRxInvalidFrameCounter(), dll->getRxUnknownControlCounter());
        // #endif

        // openknx.console.showMemory();
        logInfo("-", "-");
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