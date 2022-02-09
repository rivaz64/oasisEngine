#pragma once

#include <oaFlags.h>
#include <d3d11.h>

namespace oaEngineSDK {

class Flags{

 public:

  static Map<BIND::E,uint32> FLAGS;

  static Map<FILTER::E, D3D11_FILTER> FILTER_FLAGS;

  static Map<TEXTURE_ADDRESS_MODE::E, D3D11_TEXTURE_ADDRESS_MODE> TEXTURE_ADDRESS_FLAGS;

  static Map<COMPARISON_FUNC::E, D3D11_COMPARISON_FUNC> COMPARISON_FLAGS;

  static Map<FORMAT::E,DXGI_FORMAT> FORMATS;

  static Map<DS_DIMENSION::E,D3D11_DSV_DIMENSION> DS_DIMENCIONS;

  static Map<SRV_DIMENSION::E,D3D11_SRV_DIMENSION> SRV_DIMENCIONS;
};



}