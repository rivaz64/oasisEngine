#include "oaDX11Shader.h"
#include "oaDX11GraphicAPI.h"

#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>

namespace oaEngineSDK{

bool
oaEngineSDK::DX11Shader::compileFromFile(String file)
{
  HRESULT hr = S_OK;

  ID3DBlob* blob = nullptr;

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


  hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  device->CreateVertexShader(blob->GetBufferPointer(), 
                             blob->GetBufferSize(), 
                             nullptr, 
                             &g_pVertexShader);

  createInputLayout(blob);

  return true;
}

void DX11Shader::createInputLayout(ID3DBlob*& blob)
{
  ID3D11ShaderReflection* reflection = nullptr;
  HRESULT hr = D3DReflect(blob->GetBufferPointer(), 
             blob->GetBufferSize(), 
             IID_ID3D11ShaderReflection, 
             reinterpret_cast<void**>(&reflection));

  D3D11_SHADER_DESC shaderDesc;
  reflection->GetDesc(&shaderDesc);
  Vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
  for (uint32 i = 0; i < shaderDesc.InputParameters; ++i){
    D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
    reflection->GetInputParameterDesc(i, &paramDesc);

    D3D11_INPUT_ELEMENT_DESC elementDesc;
    elementDesc.SemanticName = paramDesc.SemanticName;
    elementDesc.SemanticIndex = paramDesc.SemanticIndex;
    elementDesc.InputSlot = 0;
    elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    elementDesc.InstanceDataStepRate = 0;

    if (paramDesc.Mask == 1){
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 3){
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 7){
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 15){
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
    }

    inputLayoutDesc.push_back(elementDesc);

  }

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  device->CreateInputLayout(&inputLayoutDesc[0], 
                            inputLayoutDesc.size(), 
                            blob->GetBufferPointer(), 
                            blob->GetBufferSize(), &inputLayout);

  reflection->Release();
  blob->Release();

}

}