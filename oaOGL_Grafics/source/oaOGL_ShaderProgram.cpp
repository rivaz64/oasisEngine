#include "oaOGL_ShaderProgram.h"
#include "oaOGL_Shader.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

OGL_ShaderProgram::OGL_ShaderProgram()
{
  id = glCreateProgram();
}

void 
OGL_ShaderProgram::attach(SPtr<Shader> shader)
{
  glAttachShader(id,cast<OGL_Shader>(shader)->id);
}

void 
OGL_ShaderProgram::set()
{
  glLinkProgram(id);
}

}

