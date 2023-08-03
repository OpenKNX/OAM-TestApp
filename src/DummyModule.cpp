#include "DummyModule.h"

DummyModule::DummyModule() {}

const std::string DummyModule::name()
{
    return "Dummy";
}

const std::string DummyModule::version()
{
    return MAIN_Version;
}

void DummyModule::setup(bool configured)
{
    delay(1000);
    logInfoP("Setup0");
}

void DummyModule::loop(bool configured)
{
    if (delayCheck(_timer1, 5100))
    {
        logInfoP("Loop0");
        _timer1 = millis();
    }
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
        logInfoP("Loop1");
        _timer2 = millis();
    }
}
#endif

void DummyModule::processInputKo(GroupObject &ko)
{
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

    return false;
}