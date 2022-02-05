#include "oaDX11VertexShader.h"
#include "oaDX11GraphicAPI.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <iostream>
#include<Windows.h>

namespace oaEngineSDK{
DX11VertexShader::~DX11VertexShader()
{
  if( m_shader ) m_shader->Release();
  if( m_inputLayout ) m_inputLayout->Release();
}
bool
DX11VertexShader::compileFromFile(String file)
{
  m_version = "vs_4_0";

  if(!DX11Shader::compileFromFile("shader/" + file + ".hlsl")){
    return false;
  }

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  m_device->CreateVertexShader(m_blob->GetBufferPointer(), 
                               m_blob->GetBufferSize(), 
                               nullptr, 
                               &m_shader);
  
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
    m_context->VSSetShader( m_shader, NULL, 0 );

  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_context->IASetInputLayout( m_inputLayout );
}

void 
DX11VertexShader::createInputLayout()
{
  ID3D11ShaderReflection* reflection = nullptr;
  D3DReflect(m_blob->GetBufferPointer(), 
             m_blob->GetBufferSize(), 
             IID_ID3D11ShaderReflection, 
             reinterpret_cast<void**>(&reflection));

  D3D11_SHADER_DESC shaderDesc;
  reflection->GetDesc(&shaderDesc);
  int32 actual = 0;
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

    
    elementDesc.AlignedByteOffset = actual;
    if (paramDesc.Mask == 1){
      
      actual +=4;
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 3){
      actual +=8;
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 7){
      actual +=12;
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
    }

    else if (paramDesc.Mask <= 15){
      actual +=16;
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32){
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
    }

    inputLayoutDesc.push_back(elementDesc);

  }

  //inputLayoutDesc[0].AlignedByteOffset = 0;
  //inputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
    m_device->CreateInputLayout(&inputLayoutDesc[0], 
                              static_cast<uint32>(inputLayoutDesc.size()), 
                              m_blob->GetBufferPointer(), 
                              m_blob->GetBufferSize(), &m_inputLayout);//*/

  //reflection->Release();
  m_blob->Release();

}

}