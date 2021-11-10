#include "oaOGL_Buffer.h"
#include "oaMesh.h"
#include "oaOGL_GraphicsAPI.h"
#include "oaMatrix4f.h"
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

bool 
OGL_Buffer::init(void* data, uint32 size,BUFFER_FLAGS flags)
{
  if(flags == BUFFER_FLAGS::VERTEX){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(FLAGS[flags], VBO);
    glBufferData(FLAGS[flags], size, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); 
  }

  if(flags == BUFFER_FLAGS::INDEX){
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
  }
  
  return true;

}

void 
OGL_Buffer::update(void* data)
{
  memcpy(pointer,data,sizeof(Matrix4f));
  /*unsigned int transformLoc = glGetUniformLocation(
    reinterpret_cast<OGL_GraphicsAPI*>(OGL_GraphicsAPI::instancePtr())->shaderProgram, 
    "transform");
  glUniformMatrix4fv(0, 1, GL_FALSE, reinterpret_cast<float*>(data));*/

}

}

