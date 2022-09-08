#include "oaShaderProgram.h"
#include "oaShader.h"

namespace oaEngineSDK{

ShaderProgram::ShaderProgram(const Vector<WPtr<Shader>>& shaders)
{
  for(auto& shader : shaders){
    attach(shader);
  }
}

}

