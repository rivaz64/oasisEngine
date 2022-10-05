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
  createModel(const String& name, WPtr<Actor> actor) override;

  void
  connectToModel(const String& name, WPtr<Actor> scene) override;

  void
  addScene(WPtr<Actor> actor);

  void
  closeScene() override;

  void
  createSession(const String& name);

  void
  joinToSession(const String& name);

  void
  leaveSession();

  void
  update() override;

protected:

  String m_userFolder = "omniverse://localhost/Users";
  String m_userName;
  String m_destinationPath;
  String m_stageUrl;
  
  Vector<WPtr<Actor>> m_actors;

  WPtr<Actor> m_scene;

  friend class OmniverseApi;
  friend class Module<OmniverseApi>;
};

}


