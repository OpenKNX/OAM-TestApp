#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "VirtualButtonModule.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
#endif

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, new Logic());
    openknx.addModule(2, new DummyModule());
    openknx.addModule(3, new VirtualButtonModule());
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(9, new FileTransferModule());
#endif
    openknx.setup();

    // openknx.progLed.off();
    // openknx.progLed.on();
    openknx.progLed.blinking();
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
}

void loop1()
{
    openknx.loop1();
    _debugCore1 = millis();
}
#endif