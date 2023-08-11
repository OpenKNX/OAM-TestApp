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
    const uint8_t firmwareRevision = 1;
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
// bool d = false;
uint8_t counterTable[] = {255, 254, 252, 248, 240, 224, 192, 128, 0};
uint8_t counter = 0;
void loop()
{

    if (delayCheck(x1, 1000))
    {

        logInfo("Counter", "%i %i", counter, counterTable[counter]);

        uint8_t reCounter = counterTable[counter];
        uint8_t index = std::distance(std::begin(counterTable), std::find(std::begin(counterTable), std::end(counterTable), reCounter));
        logInfo("ReCounter", "%i %i", reCounter, index);

        counter++;
        if (counter > 8) counter = 0;
        x1 = millis();
        // openknx.flashOpenKNX.write(0, 0x10, 100);
        // openknx.flashOpenKNX.write(10, 0x20, 80);
        // openknx.flashOpenKNX.commit();
        // logHexInfo("FlashContent", openknx.flashOpenKNX.flashAddress(), 256);
    }

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