#include "OGL_Shader.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>
#include<fstream>

namespace oaEngineSDK{

bool 
OGL_Shader::compileFromFile(String file)
{
  std::fstream f;
  String s;
  f.open(file+".ogl",std::ios_base::out);
  id = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(id,1,f.get())
  return false;
}

}

