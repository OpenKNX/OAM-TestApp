#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "UpdaterModule.h"
#endif

uint32_t x1 = 0;
uint8_t x2 = 0;

void setup()
{
    const uint8_t firmwareRevision = 2;
    openknx.init(firmwareRevision);
    openknx.addModule(1, new Logic());
    openknx.addModule(2, new DummyModule());
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(9, new UpdaterModule());
#endif
    openknx.setup();

    // openknx.progLed.off();
    // openknx.progLed.on();
    // openknx.progLed.blinking();
    openknx.progLed.pulsing();
}

void loop()
{
    openknx.loop();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
}
#endif