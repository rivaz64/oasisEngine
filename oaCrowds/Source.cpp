#include "oaMobSim.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  CrowdSim::startUp<MobSim>();
}

}