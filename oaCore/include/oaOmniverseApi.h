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

  virtual bool
  connect() {return false;}

  virtual String
  getConnectedUsername() {return "";}

  virtual void
  createModel(const String& name) {}

  virtual void
  connectToModel(const String& name, WPtr<Actor> scene) {}

  virtual void
  addScene(WPtr<Actor> actor){}

  virtual void
  update(){}

 protected:

  OmniverseApi() {print("parent constructed"); }

  friend class Module<OmniverseApi>;
};

}


