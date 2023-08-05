#include "DummyModule.h"
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "UpdaterModule.h"
#endif

uint32_t x1 = 0;
uint8_t x2 = 0;
OpenKNX::Flash::Driver *test = nullptr;

void setup()
{
    const uint8_t firmwareRevision = 1;
    openknx.init(firmwareRevision);
    // openknx.addModule(1, new Logic());
    openknx.addModule(2, new DummyModule());
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(9, new UpdaterModule());
#endif
    openknx.setup();
#ifdef ARDUINO_ARCH_ESP32
    logInfo("Flash", "Size %i", spi_flash_get_chip_size());
    test = new OpenKNX::Flash::Driver(0x2b0000, 0x2000, "Test");
    test->eraseSector(0);
#endif
}

void loop()
{
    // if (delayCheck(x1, 5000))
    // {
    //     x1 = millis();
    //     test->write(x2 , (uint8_t)x1, 1);
    //     test->commit();
    //     logHexInfo("FlashContent", test->flashAddress(), 256);
    //     x2 += 1;
    // }
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