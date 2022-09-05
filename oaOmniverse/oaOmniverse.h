/**
* @file oaOmniverse.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 8/31/2022
*/

#pragma once

#include "oaOmniverseApi.h"

namespace oaEngineSDK
{

class Omniverse :
  public OmniverseApi
{
 public:

  void
  onStartUp() override;

  void
  onShutDown() override;

  void
  connect() override;

  String
  getConnectedUsername(String stageUrl) override;

protected:

  Omniverse() {print("child constructed"); }

  friend class OmniverseApi;
  friend class Module<OmniverseApi>;
};

}


