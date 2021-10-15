#include "oaDX11Shader.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

bool 
oaEngineSDK::DX11Shader::compileFromFile(String file)
{
  HRESULT hr = S_OK;

  ID3DBlob* blob = NULL;

  ID3DBlob* errorBlob;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  hr = D3DX11CompileFromFile( (file+".dx11").c_str(), NULL, NULL, "main", "vs_4_0", 
                             dwShaderFlags, 0, NULL, &blob, &errorBlob, NULL );

  if( FAILED(hr) )
  {
    if( errorBlob != NULL ){
      MessageBox( NULL,
"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );

    }

    if( errorBlob )
    {
      errorBlob->Release();
    }

    return false;
  }

  if( errorBlob ){
    errorBlob->Release();
  }

  return true;
}

}