#include "oaShaderProgram.h"
#include "oaShader.h"

namespace oaEngineSDK{

ShaderProgram::ShaderProgram(const Vector<SPtr<Shader>>& shaders)
{
  for(auto& shader : shaders){
    attach(shader);
  }
}

}

