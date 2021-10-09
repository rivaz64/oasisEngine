#include "blob.h"
#include "Shader.h"
#include <fstream>

bool Shader::loadFromFile(oaEngineSDK::String file)
{
  std::fstream fs;
  fs.open (file, std::fstream::in | std::fstream::out | std::fstream::app);
  code = fs.get();
  fs.close();
  return true;
}

bool Shader::compile()
{
  blob* b = (blob*)buf->get();
  //ID3DBlob* blob = NULL;
  HRESULT hr = D3DCompile(
    code.c_str(),
    code.length(),
    nullptr,
    nullptr,
    nullptr,
    "VS", "vs_4_0",
    D3DCOMPILE_ENABLE_STRICTNESS, 0,
    &b->blo,
  nullptr);

  if(FAILED(hr)){
    return false;
  }

}
