#include "oaGaInput.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  InputAPI::startUp<GaInput>();
}

}