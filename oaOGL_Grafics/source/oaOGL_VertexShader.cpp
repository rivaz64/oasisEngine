#include "oaOGL_VertexShader.h"
#include"oaOGL_GraphicsAPI.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

bool 
OGL_VertexShader::compileFromFile(String file)
{
  id = glCreateShader(GL_VERTEX_SHADER);

  if(!OGL_Shader::compileFromFile(file + "/vertexShader.glsl")){
    return false;
  }

  return true;
}

}

