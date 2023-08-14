#include "DummyChannel.h"
#include "Arduino.h"

DummyChannel::DummyChannel(uint8_t index)
{
    _channelIndex = index;
}

const std::string DummyChannel::name()
{
    return "DummyChannel";
}

void DummyChannel::setup()
{
    logInfoP("setup");
    logIndentUp();
    logDebugP("debug setup");
    logTraceP("trace setup");
    logIndentDown();
}

void DummyChannel::loop()
{
  // Dummy Action
  delayMicroseconds(100);
}