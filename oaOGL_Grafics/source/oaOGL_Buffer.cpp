#include "oaOGL_Buffer.h"
#include "oaMesh.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

Map<BUFFER_FLAGS,uint32> FLAGS = {
  {BUFFER_FLAGS::VERTEX,GL_ARRAY_BUFFER}
  //{BUFFER_FLAGS::CONSTANT,D3D11_BIND_CONSTANT_BUFFER},
};

OGL_Buffer::~OGL_Buffer()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void OGL_Buffer::init(void* data, uint32 size,BUFFER_FLAGS flags)
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(FLAGS[flags], VBO);
  glBufferData(FLAGS[flags], size, data, GL_STATIC_DRAW);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  //glBindVertexArray(0); 

}

void OGL_Buffer::update(void* data, uint32 size)
{
}

}

