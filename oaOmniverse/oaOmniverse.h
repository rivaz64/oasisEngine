/**
* @file oaOmniverse.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 8/31/2022
*/

#pragma once

#include "oaOmniverseApi.h"
//#include <pxr/usd/usd/stage.h>

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

  bool
  connect() override;

  String
  getConnectedUsername() override;

  void
  createModel(const String& name) override;

  void
  addMesh(WPtr<StaticMesh> mesh) override;

protected:

  Omniverse() {print("child constructed"); }

  String m_userFolder = "omniverse://localhost/Users";
  String m_userName;
  String m_destinationPath;

  friend class OmniverseApi;
  friend class Module<OmniverseApi>;
};

}


