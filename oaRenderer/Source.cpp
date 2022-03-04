
#include"oaDeferred.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  Renderer::startUp<Deferred>();
}

}