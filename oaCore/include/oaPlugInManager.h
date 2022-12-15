#pragma once
#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT PlugInManager:
  public Module<PlugInManager>
{
 public:

  void
  load(String DLL);

  friend class Module<PlugInManager>;
};

}


