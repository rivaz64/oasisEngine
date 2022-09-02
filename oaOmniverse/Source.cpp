#include "oaOmniverse.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  OmniverseApi::startUp<Omniverse>();
  auto& omnievrse = OmniverseApi::instance();
}

}