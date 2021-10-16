#include "oaOGL_Shader.h"

#include<glad\glad.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include <sstream>
#include <iostream>

namespace oaEngineSDK{

bool 
OGL_Shader::compileFromFile(String file)
{
  id = glCreateShader(GL_VERTEX_SHADER);
  std::fstream f;
  String completeFile = file+".ogl";
  f.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  f.open(completeFile);
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
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    return false;
  };



  return true;
}

}