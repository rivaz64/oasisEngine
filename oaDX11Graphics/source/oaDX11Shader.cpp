#include "oaDX11Shader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

bool 
DX11Shader::readFromFile(String file, const Vector<String>& defines, ID3DBlob** blob)
{
  HRESULT hr = S_OK;

  ID3DBlob* errorBlob;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
  Vector<D3D10_SHADER_MACRO> shaderDefines;
  SIZE_T numDefines = defines.size();
  shaderDefines.resize(numDefines);
  for(SIZE_T defineNum = 0; defineNum < numDefines; ++defineNum){
    shaderDefines[defineNum].Name = defines[defineNum].c_str();
  }

  D3D10_SHADER_MACRO terminator;
  memset(&terminator,0,sizeof(D3D10_SHADER_MACRO));
  shaderDefines.push_back(terminator);

  if(numDefines>0){
    hr = D3DX11CompileFromFile(file.c_str(),
                               shaderDefines.data(), 
                               NULL, 
                               "main", 
                               m_version.c_str(), 
                               dwShaderFlags, 
                               0, 
                               NULL, 
                               (ID3DBlob**)blob, 
                               &errorBlob, 
                               NULL );
  }
  else{
    hr = D3DX11CompileFromFile(file.c_str(),
                               NULL, 
                               NULL, 
                               "main", 
                               m_version.c_str(), 
                               dwShaderFlags, 
                               0, 
                               NULL, 
                               (ID3DBlob**)blob, 
                               &errorBlob, 
                               NULL );
  }
  
  if( FAILED(hr) )
  {

    if( errorBlob )
    {
      print("shader failed to compile");
      print((char*)errorBlob->GetBufferPointer());
      errorBlob->Release();
    }
    else{
      print("shader not found "+file);
    }

    return false;
  }

  if( errorBlob ){
    errorBlob->Release();
  }

  return true;
}


}
