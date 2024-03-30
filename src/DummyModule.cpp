#include "DummyModule.h"

DummyModule::DummyModule() {}

const std::string DummyModule::name()
{
    return "Dummy";
}

const std::string DummyModule::version()
{
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
}

void DummyModule::setup(bool configured)
{
    // delay(1000);
    // logInfoP("Setup0");
    logIndentUp();

    setupCustomFlash();
    setupChannels();

    logIndentDown();
}

void DummyModule::setupChannels()
{
    for (uint8_t i = 0; i < DMY_ChannelCount; i++)
    {
        _channels[i] = new DummyChannel(i);
        _channels[i]->setup();
    }
}

void DummyModule::setupCustomFlash()
{
    logDebugP("initialize dummy flash");
    OpenKNX::Flash::Driver _dummyStorage;
#ifdef ARDUINO_ARCH_ESP32
    _dummyStorage.init("dummy");
#else
    _dummyStorage.init("dummy", DUMMY_FLASH_OFFSET, DUMMY_FLASH_SIZE);
#endif

    logTraceP("write dummy data");
    // _dummyStorage.writeByte(0, 0x11);
    // _dummyStorage.writeWord(1, 0xFFFF);
    // _dummyStorage.writeInt(3, 6666666);
    // for (size_t i = 0; i < 4095; i++)
    // {
    //     _dummyStorage.writeByte(i, i);
    // }
    // _dummyStorage.commit();

    logDebugP("read dummy data");
    logIndentUp();
    // logHexDebugP(_dummyStorage.flashAddress(), 4095);
    // logDebugP("byte: %02X", _dummyStorage.readByte(0)); // UINT8
    // logDebugP("word: %i", _dummyStorage.readWord(1));   // UINT16
    // logDebugP("int: %i", _dummyStorage.readInt(3));     // UINT32

    logIndentDown();
}

void DummyModule::loop(bool configured)
{
    // if (delayCheck(_timer1, 5100))
    // {
    //     // logInfoP("Loop0");
    //     _timer1 = millis();
    // }

    // // counter for processed channels in one loop
    // uint8_t channelProcessed = 0;

    // // skip when the free time has been used up or all channels have already been processed once.
    // while (channelProcessed < DMY_ChannelCount && openknx.freeLoopTime())
    // {
    //     if (_channelIterator >= DMY_ChannelCount) _channelIterator = 0;

    //     _channels[_channelIterator]->loop();
    //     _channelIterator++;
    //     channelProcessed++;
    // }
}

#ifdef OPENKNX_DUALCORE

void DummyModule::setup1(bool configured)
{
    delay(1000);
    logInfoP("Setup1");
}

void DummyModule::loop1(bool configured)
{
    if (delayCheck(_timer2, 7200))
    {
        // logInfoP("Loop1");
        _timer2 = millis();
    }
}
#endif

void DummyModule::processInputKo(GroupObject& ko)
{
    logDebugP("processInputKo GA%04X", ko.asap());
    logHexDebugP(ko.valueRef(), ko.valueSize());
}

void DummyModule::showHelp()
{
    openknx.console.printHelpLine("dummy", "Print a dummy text");
}

bool DummyModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.substr(0, 5) == "dummy")
    {
        logInfoP("Dummy Info");
        logIndentUp();
        logInfoP("Info 1");
        logInfoP("Info 2");
        logIndentUp();
        logInfoP("Info 2a");
        logInfoP("Info 2b");
        logIndentDown();
        logInfoP("Info 3");
        logIndentDown();
        return true;
    }

//     TpUartDataLinkLayer* dll = knx.bau().getDataLinkLayer();
//     if (cmd.compare("tp mon") == 0)
//     {
//         logInfo("KNX<TP>", "Starting tpuart in bus monitor");
//         dll->monitor();
//         return true;
//     }
//     else if (cmd.compare("tp rst") == 0)
//     {
//         logInfo("KNX<TP>", "Reset tpuart");
//         dll->reset();
//         return true;
//     }
//     else if (cmd.compare("tp stats") == 0)
//     {
//         logInfo("KNX<TP>", "ProcessedFrames: %i - IgnoredFrames: %i - InvalidFrames: %i - UnknownControl: %i",
//                 dll->getRxProcessdFrameCounter(), dll->getRxIgnoredFrameCounter(), dll->getRxInvalidFrameCounter(), dll->getRxUnknownControlCounter());
//         return true;
//     }
//     else if (cmd.compare("tp stop") == 0)
//     {
//         logInfo("KNX<TP>", "Stop tpuart");
//         dll->stop(true);
//         return true;
//     }
//     else if (cmd.compare("tp resume") == 0)
//     {
//         logInfo("KNX<TP>", "Resume tpuart");
//         dll->stop(false);
//         return true;
//     }
// #ifdef NCN5120
//     else if (cmd.compare("tp poff") == 0)
//     {
//         logInfo("KNX<TP>", "Poweroff tpuart VCC2");
//         dll->powerControl(false);
//         return true;
//     }
//     else if (cmd.compare("tp pon") == 0)
//     {
//         logInfo("KNX<TP>", "Poweron tpuart VCC2");
//         dll->powerControl(true);
//         return true;
//     }
// #endif

    return false;
}

#ifdef ARDUINO_ARCH_RP2040
void DummyModule::registerUsbExchangeCallbacks()
{
    // Sample
    openknxUsbExchangeModule.onLoad("Dummy.txt", [](UsbExchangeFile* file) -> void {
        file->write("Demo");
    });
    openknxUsbExchangeModule.onEject("Dummy.txt", [](UsbExchangeFile* file) -> bool {
        // File is required
        if (file == nullptr)
        {
            logError("DummyModule", "File Dummy.txt was deleted but is mandatory");
            return false;
        }
        return true;
    });
}
#endif

DummyModule openknxDummyModule;