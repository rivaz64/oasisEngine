
#include "oaDX11GraphicAPI.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

OA_EXTERN OA_PLUGIN_EXPORT void
initPlugIn(){
  GraphicAPI::startUp<DX11GraphicAPI>();
  GraphicAPI::instancePtr()->actualGraphicAPI = GRAPHIC_API::DIRECTX11;
}

}
