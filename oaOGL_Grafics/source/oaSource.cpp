#include "oaPrerequisitesOGL.h"
#include "oaOGL_GraphicsAPI.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  GraphicAPI::startUp<OGL_GraphicsAPI>();
  GraphicAPI::instancePtr()->
}

}