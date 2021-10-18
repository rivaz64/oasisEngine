#pragma once

#include "oaBaseApp.h"

namespace oaEngineSDK{

class TestApp :
  public BaseApp
{
public:

  void
  run() override;

  void 
  postInit() override;
};

}


