#include "oaDX11ShaderProgram.h"
#include <oaShader.h>

namespace oaEngineSDK{

void 
DX11ShaderProgram::attach(SPtr<Shader> shader)
{
  m_shaders.push_back(shader);
}

void
DX11ShaderProgram::set()
{
  for(SPtr<Shader> shader: m_shaders){
    shader->set();
  }
}

}

