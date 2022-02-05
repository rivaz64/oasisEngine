#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

namespace BIND{
enum E{
  kConstant=0,
  kVertex,
  kIndex,
  kDepthStencil,
  kShaderResourse,
  kRenderTarget,
  kShaderResourseRenderTarget
};
}
 
namespace DS_DIMENSION{
enum E{
  kUnknown = 0,
  kTexture1D,
  kTexture1DArray,
  kTexture2D,
  kTexture2DArray,
  kTexture2DMS,
  kTexture2DMSArray
};
}

namespace SRV_DIMENSION{
enum E{
  kUnknown = 0,
  kBuffer,
  kTexture1D,
  kTexture1DArray,
  kTexture2D,
  kTexture2DArray,
  kTexture2DMS,
  kTexture2DMSArray,
  kTexture3D,
  kTextureCube,
  kTextureCubeArray,
  kBufferEx
};
}

namespace FILTER{
enum E{
  kMinMagMipLinear=0,
  /*MIN_MAG_MIP_POINT = 0,
  MIN_MAG_POINT_MIP_LINEAR,
  MIN_POINT_MAG_LINEAR_MIP_POINT,
  MIN_POINT_MAG_MIP_LINEAR,
  MIN_LINEAR_MAG_MIP_POINT,
  MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  MIN_MAG_LINEAR_MIP_POINT,
  MIN_MAG_MIP_LINEAR,
  ANISOTROPIC,
  COMPARISON_MIN_MAG_MIP_POINT,
  COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
  COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
  COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
  COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
  COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
  COMPARISON_MIN_MAG_MIP_LINEAR,
  COMPARISON_ANISOTROPIC,
  MINIMUM_MIN_MAG_MIP_POINT,
  MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
  MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
  MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
  MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
  MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
  MINIMUM_MIN_MAG_MIP_LINEAR,
  MINIMUM_ANISOTROPIC,
  MAXIMUM_MIN_MAG_MIP_POINT,
  MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
  MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
  MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
  MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
  MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
  MAXIMUM_MIN_MAG_MIP_LINEAR,
  MAXIMUM_ANISOTROPIC*/
};
}

namespace TEXTURE_ADDRESS_MODE{
enum E{
  kWrap=0,
  kMirror,
  kClamp,
  kBorder,
  kMirrorOnce
};
}

namespace COMPARISON_FUNC{
enum E{
  kNever=0,
  kLess,
  kEqual,
  kLessEqual,
  kGreater,
  kNotEqual,
  kGreaterEqual,
  kAlways
};
}

namespace FORMAT{
enum E{
  kD24UNormS8UInt = 0,
  kR32G32B32A32Float
};
}

namespace COMPONENT_TYPE{
enum E{
  kNone = 0,
  kGrpahics,
  kSkeleton,
  kAnimation
};
}

}