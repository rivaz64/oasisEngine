#include "oaDX11SamplerState.h"
#include "oaDX11GraphicAPI.h"
#include "oaDX11Flags.h"

namespace oaEngineSDK {

DX11SamplerState::~DX11SamplerState()
{
  if (m_samplerState) m_samplerState->Release();
}

bool DX11SamplerState::init(TEXTURE_ADDRESS_MODE::E textureAdressMode)
{
  D3D11_SAMPLER_DESC sampDesc;

  memset(&sampDesc, 0, sizeof(sampDesc));

  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

  sampDesc.AddressU = Flags::TEXTURE_ADDRESS_FLAGS[textureAdressMode];

  sampDesc.AddressV = Flags::TEXTURE_ADDRESS_FLAGS[textureAdressMode];

  sampDesc.AddressW = Flags::TEXTURE_ADDRESS_FLAGS[textureAdressMode];

  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

  sampDesc.MinLOD = -Math::MAX_FLOAT;

  sampDesc.MaxLOD = Math::MAX_FLOAT;

  HRESULT hr = reinterpret_cast<DX11GraphicAPI*>(DX11GraphicAPI::instancePtr())->
  m_device->CreateSamplerState( &sampDesc, &m_samplerState );

  if( FAILED( hr ) )
    return false;

  return true;
}

}

