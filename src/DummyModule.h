#pragma once
#include "OpenKNX.h"
#include "DummyChannel.h"

#define DMY_ChannelCount 10

class DummyModule : public OpenKNX::Module
{
  private:
    uint8_t _channelIterator = 0;
    uint32_t _timer1 = 0;
    uint32_t _timer2 = 0;
    DummyChannel *_channels[DMY_ChannelCount];
    OpenKNX::Flash::Driver * _dummyStorage = nullptr;

    void setupCustomFlash();
    void setupChannels();

  public:
    DummyModule();
    void loop(bool configured) override;
    void setup(bool configured) override;
#ifdef OPENKNX_DUALCORE
    void loop1(bool configured) override;
    void setup1(bool configured) override;
#endif
    const std::string name() override;
    const std::string version() override;
    void processInputKo(GroupObject &ko) override;
    bool processCommand(const std::string cmd, bool diagnoseKo);
    void showHelp() override;
};