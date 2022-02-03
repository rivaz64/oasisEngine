#include "oaDX11Shader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

bool DX11Shader::compileFromFile(String file)
{
  HRESULT hr = S_OK;

  ID3DBlob* errorBlob;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  hr = D3DX11CompileFromFile( file.c_str(), NULL, NULL, "main", m_version.c_str(), 
                             dwShaderFlags, 0, NULL, &m_blob, &errorBlob, NULL );

  if( FAILED(hr) )
  {

    if( errorBlob )
    {
      print("shader failed to compile");
      print((char*)errorBlob->GetBufferPointer());
      errorBlob->Release();
    }
    else{
      std::cout<<"shader not found"<<std::endl;
    }

    return false;
  }

  if( errorBlob ){
    errorBlob->Release();
  }

  return true;
}


}
