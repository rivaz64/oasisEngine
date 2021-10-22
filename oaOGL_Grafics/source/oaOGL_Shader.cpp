#include "oaOGL_Shader.h"
#include "oaOGL_GraphicsAPI.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include <sstream>
#include <iostream>

namespace oaEngineSDK{

OGL_Shader::~OGL_Shader()
{
  glDeleteShader(id);
}

bool
OGL_Shader::compileFromFile(String file)
{
  std::fstream f;
  f.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  f.open(file);
  if(!f.is_open()){
    std::cout << "failed to find shader" << std::endl;
    return false;
  }
  std::stringstream ss;
  ss << f.rdbuf();
  String s = ss.str();
  int size = s.size();
  const char* str = s.c_str();
  glShaderSource(id,1,&str,&size);
  glCompileShader(id);
  int success;
  glGetShaderiv(id,GL_COMPILE_STATUS,&success);

  if(!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(id,512, NULL, infoLog);
    std::cout << "failed to compile shader" << std::endl;
    std::cout << file << std::endl;
    std::cout << infoLog << std::endl;
    return false;
  };

  glAttachShader(
  reinterpret_cast<OGL_GraphicsAPI*>(OGL_GraphicsAPI::instancePtr())->shaderProgram, id);

  return true;
}

}