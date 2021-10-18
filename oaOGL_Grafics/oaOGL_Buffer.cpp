#include "oaOGL_Buffer.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

void oaEngineSDK::oaOGL_Buffer::init(void* data, uint32 size)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);  
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
