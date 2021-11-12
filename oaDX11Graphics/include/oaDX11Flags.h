#pragma once

#include "oaFlags.h"
#include <d3d11.h>

namespace oaEngineSDK {

class Flags{

 public:

  static Map<BIND,uint32> FLAGS;

  static Map<FILTER, D3D11_FILTER> FILTER_FLAGS;

  static Map<TEXTURE_ADDRESS_MODE, D3D11_TEXTURE_ADDRESS_MODE> TEXTURE_ADDRESS_FLAGS;

  static Map<COMPARISON_FUNC, D3D11_COMPARISON_FUNC> COMPARISON_FLAGS;

  static Map<FORMAT,DXGI_FORMAT> FORMATS;

};



}