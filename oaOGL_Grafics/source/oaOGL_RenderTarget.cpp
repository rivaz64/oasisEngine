#include "oaOGL_RenderTarget.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

bool OGL_RenderTarget::init(SPtr<Texture> texture)
{
  glGenFramebuffers(1, &m_id);
  //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
  return false;
}

}

