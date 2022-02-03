#include "oaOGL_IndexBuffer.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

bool 
OGL_IndexBuffer::init(Vector<uint32>& data)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size(), data.data(), GL_STATIC_DRAW); 
}

void 
OGL_IndexBuffer::set()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

}

