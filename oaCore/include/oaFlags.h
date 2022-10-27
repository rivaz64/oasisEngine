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
  kRenderTarget
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
  kR24G8 = 0,
  kR32G32B32A32Float,
  kB8G8R8A8UnormSRGB,
};
}

namespace COMPONENT_TYPE{
enum E{
  kNone = 0,
  kGrpahics,
	kStaticMesh,
	kSkeletalMesh,
	kDirectionalLight,
	kCamera
};
}

namespace PRIMITIVE_TOPOLOGY{
enum E{
  kPointList=0,
  kLineList,
  kLineStrip,
  kTrianlgeList,
  kTrianlgeStrip,
	k1ContolPointPathlist,
	k2ContolPointPathlist,
	k3ContolPointPathlist,
	k4ContolPointPathlist,
	k5ContolPointPathlist,
	k6ContolPointPathlist,
	k7ContolPointPathlist,
	k8ContolPointPathlist,
	k9ContolPointPathlist,
	k10ContolPointPathlist,
	k11ContolPointPathlist,
	k12ContolPointPathlist,
	k13ContolPointPathlist,
	k14ContolPointPathlist,
	k15ContolPointPathlist,
	k16ContolPointPathlist,
	k17ContolPointPathlist,
	k18ContolPointPathlist,
	k19ContolPointPathlist,
	k20ContolPointPathlist,
	k21ContolPointPathlist,
	k22ContolPointPathlist,
	k23ContolPointPathlist,
	k24ContolPointPathlist,
	k25ContolPointPathlist,
	k26ContolPointPathlist,
	k27ContolPointPathlist,
	k28ContolPointPathlist,
	k29ContolPointPathlist,
	k30ContolPointPathlist,
	k31ContolPointPathlist,
	k32ContolPointPathlist,
};
}

namespace FILE{
enum E{
  kRead,
  kWrite
};
}

namespace KEY{
enum E{
  kEscape=0,
	kF1,
	kF2,
	kF3,
	kF4,
	kF5,
	kF6,
	kF7,
	kF8,
	kF9,
	kF10,
	kF11,
	kF12,
	kPrint,
	kScrollLock,
	kBreak,
	kSpace,
	kApostrophe,
	kComma,
	kMinus,
	kPeriod,
	kSlash,
	k0,
	k1,
	k2,
	k3,
	k4,
	k5,
	k6,
	k7,
	k8,
	k9,
	kSemicolon,
	kLess,
	kEqual,
	kA,
	kB,
	kC,
	kD,
	kE,
	kF,
	kG,
	kH,
	kI,
	kJ,
	kK,
	kL,
	kM,
	kN,
	kO,
	kP,
	kQ,
	kR,
	kS,
	kT,
	kU,
	kV,
	kW,
	kX,
	kY,
	kZ,
	kBracketLeft,
	kBackslash,
	kBracketRight,
	kGrave,
	kLeft,
	kRight,
	kUp,
	kDown,
	kInsert,
	kHome,
	kDelete,
	kEnd,
	kPageUp,
	kPageDown,
	kNumLock,
	kKpEqual,
	kKpDivide,
	kKpMultiply,
	kKpSubtract,
	kKpAdd,
	kKpEnter,
	kKpInsert, 
	kKpEnd, 
	kKpDown, 
	kKpPageDown, 
	kKpLeft,
	kKpBegin,
	kKpRight, 
	kKpHome, 
	kKpUp, 
	kKpPageUp,
	kKpDelete,
	kBackSpace,
	kTab,
	kReturn,
	kCapsLock,
	kShiftL,
	kCtrlL,
	kSuperL,
	kAltL,
	kAltR,
	kSuperR,
	kMenu,
	kCtrlR,
	kShiftR,
	kLastkey,
};
}

namespace BUTTON{
enum E{
kLeft = KEY::kLastkey,
kRight,
kMiddle,
kLastButton,
};
}

namespace AXIS{
enum E{
kX = BUTTON::kLastButton,
kY
};
}

}

