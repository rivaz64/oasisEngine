#include "oaOGL_DepthStencil.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

bool OGL_DepthStencil::init(DepthStencilDesc descritor, SPtr<Texture> texture)
{
  glEnable(GL_STENCIL_TEST);
}

}

