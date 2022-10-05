#include "oaAdaptativeShader.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK
{

void
createPixelShaders(const String& name, const Vector<String>& allDefines,Vector<SPtr<Shader>>& shaders, Vector<String>& defines, int num)
{
  auto& graphicsApi = GraphicAPI::instance();
  if(num < allDefines.size()){
    createPixelShaders(name,allDefines,shaders, defines, num+1);
    defines.push_back(allDefines[num]);
    createPixelShaders(name,allDefines,shaders, defines, num+1);
    defines.pop_back();
  }
  else{
    auto shader = graphicsApi.createPixelShader();
    shader->compileFromFile(name,defines);
    shaders.push_back(shader);
  }
}

bool 
AdaptativeShader::compile(const String& name, const Vector<String>& allDefines)
{
  Vector<String> defines;
  createPixelShaders(name,allDefines,m_shaders,defines,0);
  return true;
}

void
AdaptativeShader::set(uint32 flags)
{
  m_shaders[flags]->set();
}

}

