#include "oaDX11Shader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>
bool oaEngineSDK::DX11Shader::compileFromFile(String file)
{
  HRESULT hr = S_OK;

  ID3DBlob* errorBlob;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  hr = D3DX11CompileFromFile( file.c_str(), NULL, NULL, "main", version.c_str(), 
                             dwShaderFlags, 0, NULL, &blob, &errorBlob, NULL );

  if( FAILED(hr) )
  {
    if( errorBlob != NULL ){
      std::cout<<"shader failed to compile"<<std::endl;
    }

    if( errorBlob )
    {
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
}
