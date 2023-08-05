#include "DummyModule.h"
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #include "UpdaterModule.h"
#endif

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
    OpenKNX::Flash::Driver *test = new OpenKNX::Flash::Driver(0x2b0000, 0x2000, "Test");
    test->write(0x1000, 0x60, 1);
    test->commit();
    logHexInfo("Flash1", test->flashAddress(), 512);
    logHexInfo("Flash2", test->flashAddress() + 0x1000, 512);
#endif
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