#pragma once
#include "OpenKNX.h"

class DummyChannel : public OpenKNX::Channel
{
  private:

  public:
    DummyChannel(uint8_t index);
    const std::string name() override;
    void setup() override;
    void loop() override;

};