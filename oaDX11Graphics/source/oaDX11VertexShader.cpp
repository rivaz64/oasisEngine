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
DX11VertexShader::compileFromFile(const String& file,const Vector<String>& defines)
{
  m_version = "vs_5_0";

  ID3DBlob* blob;

  if(!readFromFile("shader/" + file + ".hlsl", defines, &blob)){
    return false;
  }

  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;

  HRESULT hr = device->CreateVertexShader(blob->GetBufferPointer(), 
                                          blob->GetBufferSize(), 
                                          nullptr, 
                                          &m_shader);
  
  if (FAILED(hr)) {
    return false;
  }

  if(!createInputLayout(blob)){
    return false;
  }
  
  blob->Release();

  //m_blob = blob;

  return true;
}

void 
DX11VertexShader::set()
{
  auto& context = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_context;

  context->VSSetShader( m_shader, NULL, 0 );

  context->IASetInputLayout( m_inputLayout );
}

bool 
DX11VertexShader::createInputLayout(ID3DBlob* blob)
{
  //D3D11_INPUT_ELEMENT_DESC layout[] =
  //{
  //    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  //};
	//UINT numElements = ARRAYSIZE( layout );
  //
  //auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;
  //auto& context = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_context;
  //
  //  // Create the input layout
	//device->CreateInputLayout( layout, numElements, blob->GetBufferPointer(),
  //                                        blob->GetBufferSize(), &m_inputLayout );
  //
  ID3D11ShaderReflection* reflection = nullptr;
  D3DReflect(blob->GetBufferPointer(), 
             blob->GetBufferSize(), 
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
  auto& device = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_device;
  auto& context = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->m_context;
  HRESULT hr = device->CreateInputLayout(&inputLayoutDesc[0], 
                                          static_cast<uint32>(inputLayoutDesc.size()), 
                                          blob->GetBufferPointer(), 
                                          blob->GetBufferSize(), &m_inputLayout);//*/
  context->IASetInputLayout( m_inputLayout );
  //reflection->Release();
  //m_blob->Release();
  
  if(FAILED(hr)){
    return false;
  }
  return true;
}

}