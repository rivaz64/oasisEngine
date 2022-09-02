/**
* @file oaOmniverseApi.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 8/31/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>

namespace oaEngineSDK 
{

class OA_CORE_EXPORT OmniverseApi :
  public Module<OmniverseApi>
{
 public:

  virtual void
  onStartUp() override {print("wrong start up"); }

  virtual void
  onShutDown() override {print("wrong shut down"); }

 protected:

  OmniverseApi() {print("parent constructed"); }

  friend class Module<OmniverseApi>;
};

}


