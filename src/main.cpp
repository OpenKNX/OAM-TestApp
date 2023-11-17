#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "VirtualButtonModule.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
    #include "NetworkModule.h"
    #include "UsbExchangeModule.h"
#endif

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;
bool func1test = false;
bool core1_separate_stack = true;

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, new Logic());
    openknx.addModule(2, openknxDummyModule);
    openknx.addModule(3, openknxVirtualButtonModule);
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(7, openknxNetwork);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);
#endif
    openknx.setup();

#ifdef FUNC1_BUTTON_PIN
    openknx.func1Button.onShortClick([]() -> void {
        func1test = !func1test;
        openknx.info2Led.on(func1test);
        openknx.info3Led.on(!func1test);
    });
#endif

    logInfo("Test", "FreeStack: %i bytes", rp2040.getFreeStack());
    // openknx.progLed.off();
    // openknx.progLed.on();
    // openknx.progLed.blinking();
    // openknx.progLed.pulsing();
}

void loop()
{
    openknx.loop();
    _debugCore0 = millis();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
    logInfo("Test", "FreeStack: %i bytes", rp2040.getFreeStack());
    // logInfo("Test", "StackPointer: %X   (%i)", rp2040.getStackPointer(), rp2040.separateCore1StackSize);
    // logInfo("Test", "StackAddress: 0x%X - 0x%X", (rp2040.separateCore1Stack), (rp2040.separateCore1Stack) + rp2040.separateCore1StackSize );
}

void loop1()
{
    openknx.loop1();
    _debugCore1 = millis();
}
#endif