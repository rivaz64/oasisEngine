#include "oaDX11SamplerState.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"

namespace oaEngineSDK {

DX11SamplerState::~DX11SamplerState()
{
  if (m_samplerState) m_samplerState->Release();
}

bool DX11SamplerState::init(SamplerDesc descriptor)
{
  D3D11_SAMPLER_DESC sampDesc;

  ZeroMemory(&sampDesc, sizeof(sampDesc));

  sampDesc.Filter = Flags::FILTER_FLAGS[descriptor.filter];

  sampDesc.AddressU = Flags::TEXTURE_ADDRESS_FLAGS[descriptor.addressU];

  sampDesc.AddressV = Flags::TEXTURE_ADDRESS_FLAGS[descriptor.addressV];

  sampDesc.AddressW = Flags::TEXTURE_ADDRESS_FLAGS[descriptor.addressW];

  sampDesc.ComparisonFunc = Flags::COMPARISON_FLAGS[descriptor.comparison];

  sampDesc.MinLOD = descriptor.minLOD;

  sampDesc.MaxLOD = descriptor.maxLOD;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  m_device->CreateSamplerState( &sampDesc, &m_samplerState );

  if( FAILED( hr ) )
    return false;

  return true;
}

}

