#include "oaShaderProgram.h"
#include "oaShader.h"

namespace oaEngineSDK{

void 
ShaderProgram::attach(SPtr<Shader> shader)
{
  m_shaders.push_back(shader);
}

}

