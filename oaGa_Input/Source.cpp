#include "oaGa_Input.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  Input::startUp<GaInput>();
}

}