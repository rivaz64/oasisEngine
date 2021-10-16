#include "oaOGL_PixelShader.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

bool
OGL_PixelShader::compileFromFile(String file)
{
  id = glCreateShader(GL_FRAGMENT_SHADER);

  if(!OGL_Shader::compileFromFile(file + "/vertexShader.glsl")){
    return false;
  }

  return true;
}

}


