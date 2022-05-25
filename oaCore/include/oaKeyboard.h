#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

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
};
}

class OA_CORE_EXPORT Keyboard
{

 public:
  
	Keyboard(){};

	virtual bool
	isKeyDown(const KEY::E key);

  ///**
  // * @brief map maps a key to a string
  // * @param name the name of the input
  // * @param key the key to map
  //*/
  ////virtual void
  ////map(const String& name, const KEY::E key){}

};

}


