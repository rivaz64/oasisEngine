#include "oaFM_Audio.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  AudioAPI::startUp<FM_Audio>();
}

}