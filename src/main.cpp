#include "DummyModule.h"
#include "Logic.h"
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "UpdaterModule.h"
#endif

uint32_t x1 = 0;
uint8_t x2 = 0;
// OpenKNX::Flash::Driver other(OTHER_FLASH_OFFSET, OTHER_FLASH_SIZE, "Other");

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
#ifdef ARDUINO_ARCH_ESP32
    // if (delayCheck(x1, 5000))
    // {
    //     x1 = millis();
    //     other->write(x2 , (uint8_t)x1, 1);
    //     other->commit();
    //     logHexInfo("FlashContent", other->flashAddress(), 256);
    //     x2 += 1;
    // }
#endif
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