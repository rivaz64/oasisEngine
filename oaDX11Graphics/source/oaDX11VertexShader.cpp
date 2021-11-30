#include "oaDX11VertexShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>
#include<Windows.h>

namespace oaEngineSDK{
DX11VertexShader::~DX11VertexShader()
{
  if( shader ) shader->Release();
  if( inputLayout ) inputLayout->Release();
}
bool
DX11VertexShader::compileFromFile(String file)
{
  version = "vs_4_0";

  if(!DX11Shader::compileFromFile("shader/" + file + ".hlsl")){
    return false;
  }

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  device->CreateVertexShader(blob->GetBufferPointer(), 
                               blob->GetBufferSize(), 
                               nullptr, 
                               &shader);
  
  if (FAILED(hr)) {
    return false;
  }

  createInputLayout();

  return true;
}

void 
DX11VertexShader::set()
{
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->VSSetShader( shader, NULL, 0 );

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    context->IASetInputLayout( inputLayout );
}

void 
DX11VertexShader::createInputLayout()
{
  ID3D11ShaderReflection* reflection = nullptr;
  D3DReflect(blob->GetBufferPointer(), 
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

  

  
  /*D3D11_INPUT_ELEMENT_DESC layout[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };
  UINT numElements = ARRAYSIZE( layout );
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  device->CreateInputLayout( layout, numElements, blob->GetBufferPointer(),
                                       blob->GetBufferSize(), &inputLayout );*/

  inputLayoutDesc[0].AlignedByteOffset = 0;
  inputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    device->CreateInputLayout(&inputLayoutDesc[0], 
                              inputLayoutDesc.size(), 
                              blob->GetBufferPointer(), 
                              blob->GetBufferSize(), &inputLayout);//*/

  //reflection->Release();
  blob->Release();

}

}