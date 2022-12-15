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
  createModel(const String& name, WPtr<Actor> actor) {}

  virtual void
  connectToModel(const String& name, WPtr<Actor> scene) {}

  virtual void
  addScene(WPtr<Actor> actor){}

  virtual void
  closeScene(){}

  virtual void
  createSession(const String& name) {}

  virtual void
  joinToSession(const String& name) {}

  virtual void
  leaveSession() {}

  virtual void
  update(){}

  virtual String 
  addTexure(const Path& path){return "";}

  virtual void test() {}

  virtual void
  uploadFileToOmniverse(const Path& path,const Path& omniversePath){}

 protected:

  OmniverseApi() {print("parent constructed"); }

  friend class Module<OmniverseApi>;
};

}


