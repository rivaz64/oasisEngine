#include "oaDX11Shader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

bool 
DX11Shader::readFromFile(String file,ID3DBlob** blob)
{
//  HRESULT hr = S_OK;
//
//    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//    // Setting this flag improves the shader debugging experience, but still allows 
//    // the shaders to be optimized and to run exactly the way they will run in 
//    // the release configuration of this program.
//    dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
//
//    ID3DBlob* pErrorBlob;
//    hr = D3DX11CompileFromFile( file.c_str(), NULL, NULL, "main", m_version.c_str(),
//        dwShaderFlags, 0, NULL,  &m_blob, &pErrorBlob, NULL );
//    if( FAILED(hr) )
//    {
//        if( pErrorBlob != NULL )
//            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
//        if( pErrorBlob ) pErrorBlob->Release();
//        return hr;
//    }
//    if( pErrorBlob ) pErrorBlob->Release();
//
//    return S_OK;
  HRESULT hr = S_OK;

  ID3DBlob* errorBlob;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  hr = D3DX11CompileFromFile( file.c_str(), NULL, NULL, "main", m_version.c_str(), 
                             dwShaderFlags, 0, NULL, (ID3DBlob**)blob, &errorBlob, NULL );

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
