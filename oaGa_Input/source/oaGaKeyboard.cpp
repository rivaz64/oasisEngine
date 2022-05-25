#include "oaGaKeyboard.h"
#include "oaGa_Input.h"

namespace oaEngineSDK{

GaKeyboard::GaKeyboard()
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  //inputMap.MapBool(KEY::kEscape, m_id,gainput::KeyEscape);
  //inputMap.MapBool(KEY::kF1, m_id,gainput::KeyF1);
  //inputMap.MapBool(KEY::kF2, m_id,gainput::KeyF2);
  //inputMap.MapBool(KEY::kF3, m_id,gainput::KeyF3);
  //inputMap.MapBool(KEY::kF4, m_id,gainput::KeyF4);
  //inputMap.MapBool(KEY::kF5, m_id,gainput::KeyF5);
  //inputMap.MapBool(KEY::kF6, m_id,gainput::KeyF6);
  //inputMap.MapBool(KEY::kF7, m_id,gainput::KeyF7);
  //inputMap.MapBool(KEY::kF8, m_id,gainput::KeyF8);
  //inputMap.MapBool(KEY::kF9, m_id,gainput::KeyF9);
  //inputMap.MapBool(KEY::kF10, m_id,gainput::KeyF10);
  //inputMap.MapBool(KEY::kF11, m_id,gainput::KeyF11);
  //inputMap.MapBool(KEY::kF12, m_id,gainput::KeyF12);
  //inputMap.MapBool(KEY::kPrint, m_id,gainput::KeyPrint);
  //inputMap.MapBool(KEY::kScrollLock, m_id,gainput::KeyScrollLock);
  //inputMap.MapBool(KEY::kBreak, m_id,gainput::KeyBreak);
  //inputMap.MapBool(KEY::kSpace, m_id,gainput::KeySpace);
  //inputMap.MapBool(KEY::kApostrophe, m_id,gainput::KeyApostrophe);
  //inputMap.MapBool(KEY::kComma, m_id,gainput::KeyComma);
  //inputMap.MapBool(KEY::kMinus, m_id,gainput::KeyMinus);
  //inputMap.MapBool(KEY::kPeriod, m_id,gainput::KeyPeriod);
  //inputMap.MapBool(KEY::kSlash, m_id,gainput::KeySlash);
  //inputMap.MapBool(KEY::k0, m_id,gainput::Key0);
  //inputMap.MapBool(KEY::k1, m_id,gainput::Key1);
  //inputMap.MapBool(KEY::k2, m_id,gainput::Key2);
  //inputMap.MapBool(KEY::k3, m_id,gainput::Key3);
  //inputMap.MapBool(KEY::k4, m_id,gainput::Key4);
  //inputMap.MapBool(KEY::k5, m_id,gainput::Key5);
  //inputMap.MapBool(KEY::k6, m_id,gainput::Key6);
  //inputMap.MapBool(KEY::k7, m_id,gainput::Key7);
  //inputMap.MapBool(KEY::k8, m_id,gainput::Key8);
  //inputMap.MapBool(KEY::k9, m_id,gainput::Key9);
  //inputMap.MapBool(KEY::kSemicolon, m_id,gainput::KeySemicolon);
  //inputMap.MapBool(KEY::kLess, m_id,gainput::KeyLess);
  //inputMap.MapBool(KEY::kEqual, m_id,gainput::KeyEqual);
  inputMap.MapBool(KEY::kA, m_id,gainput::KeyA);
  //inputMap.MapBool(KEY::kB, m_id,gainput::KeyB);
  //inputMap.MapBool(KEY::kC, m_id,gainput::KeyC);
  //inputMap.MapBool(KEY::kD, m_id,gainput::KeyD);
  //inputMap.MapBool(KEY::kE, m_id,gainput::KeyE);
  //inputMap.MapBool(KEY::kF, m_id,gainput::KeyF);
  //inputMap.MapBool(KEY::kG, m_id,gainput::KeyG);
  //inputMap.MapBool(KEY::kH, m_id,gainput::KeyH);
  //inputMap.MapBool(KEY::kI, m_id,gainput::KeyI);
  //inputMap.MapBool(KEY::kJ, m_id,gainput::KeyJ);
  //inputMap.MapBool(KEY::kK, m_id,gainput::KeyK);
  //inputMap.MapBool(KEY::kL, m_id,gainput::KeyL);
  //inputMap.MapBool(KEY::kM, m_id,gainput::KeyM);
  //inputMap.MapBool(KEY::kN, m_id,gainput::KeyN);
  //inputMap.MapBool(KEY::kO, m_id,gainput::KeyO);
  //inputMap.MapBool(KEY::kP, m_id,gainput::KeyP);
  //inputMap.MapBool(KEY::kQ, m_id,gainput::KeyQ);
  //inputMap.MapBool(KEY::kR, m_id,gainput::KeyR);
  //inputMap.MapBool(KEY::kS, m_id,gainput::KeyS);
  //inputMap.MapBool(KEY::kT, m_id,gainput::KeyT);
  //inputMap.MapBool(KEY::kU, m_id,gainput::KeyU);
  //inputMap.MapBool(KEY::kV, m_id,gainput::KeyV);
  //inputMap.MapBool(KEY::kW, m_id,gainput::KeyW);
  //inputMap.MapBool(KEY::kX, m_id,gainput::KeyX);
  //inputMap.MapBool(KEY::kY, m_id,gainput::KeyY);
  //inputMap.MapBool(KEY::kZ, m_id,gainput::KeyZ);
  //inputMap.MapBool(KEY::kBracketLeft, m_id,gainput::KeyBracketLeft);
  //inputMap.MapBool(KEY::kBackslash, m_id,gainput::KeyBackslash);
  //inputMap.MapBool(KEY::kBracketRight, m_id,gainput::KeyBracketRight);
  //inputMap.MapBool(KEY::kGrave, m_id,gainput::KeyGrave);
  //inputMap.MapBool(KEY::kLeft, m_id,gainput::KeyLeft);
  //inputMap.MapBool(KEY::kRight, m_id,gainput::KeyRight);
  //inputMap.MapBool(KEY::kUp, m_id,gainput::KeyUp);
  //inputMap.MapBool(KEY::kDown, m_id,gainput::KeyDown);
  //inputMap.MapBool(KEY::kInsert, m_id,gainput::KeyInsert);
  //inputMap.MapBool(KEY::kHome, m_id,gainput::KeyHome);
  //inputMap.MapBool(KEY::kDelete, m_id,gainput::KeyDelete);
  //inputMap.MapBool(KEY::kEnd, m_id,gainput::KeyEnd);
  //inputMap.MapBool(KEY::kPageUp, m_id,gainput::KeyPageUp);
  //inputMap.MapBool(KEY::kPageDown, m_id,gainput::KeyPageDown);
  //inputMap.MapBool(KEY::kNumLock, m_id,gainput::KeyNumLock);
  //inputMap.MapBool(KEY::kKpEqual, m_id,gainput::KeyKpEqual);
  //inputMap.MapBool(KEY::kKpDivide, m_id,gainput::KeyKpDivide);
  //inputMap.MapBool(KEY::kKpMultiply, m_id,gainput::KeyKpMultiply);
  //inputMap.MapBool(KEY::kKpSubtract, m_id,gainput::KeyKpSubtract);
  //inputMap.MapBool(KEY::kKpAdd, m_id,gainput::KeyKpAdd);
  //inputMap.MapBool(KEY::kKpEnter, m_id,gainput::KeyKpEnter);
  //inputMap.MapBool(KEY::kKpInsert,  m_id,gainput::KeyKpInsert);
  //inputMap.MapBool(KEY::kKpEnd,  m_id,gainput::KeyKpEnd);
  //inputMap.MapBool(KEY::kKpDown,  m_id,gainput::KeyKpDown);
  //inputMap.MapBool(KEY::kKpPageDown,  m_id,gainput::KeyKpPageDown);
  //inputMap.MapBool(KEY::kKpLeft, m_id,gainput::KeyKpLeft);
  //inputMap.MapBool(KEY::kKpBegin, m_id,gainput::KeyKpBegin);
  //inputMap.MapBool(KEY::kKpRight,  m_id,gainput::KeyKpRight);
  //inputMap.MapBool(KEY::kKpHome,  m_id,gainput::KeyKpHome);
  //inputMap.MapBool(KEY::kKpUp,  m_id,gainput::KeyKpUp);
  //inputMap.MapBool(KEY::kKpPageUp, m_id,gainput::KeyKpPageUp);
  //inputMap.MapBool(KEY::kKpDelete, m_id,gainput::KeyKpDelete);
  //inputMap.MapBool(KEY::kBackSpace, m_id,gainput::KeyBackSpace);
  //inputMap.MapBool(KEY::kTab, m_id,gainput::KeyTab);
  //inputMap.MapBool(KEY::kReturn, m_id,gainput::KeyReturn);
  //inputMap.MapBool(KEY::kCapsLock, m_id,gainput::KeyCapsLock);
  //inputMap.MapBool(KEY::kShiftL, m_id,gainput::KeyShiftL);
  //inputMap.MapBool(KEY::kCtrlL, m_id,gainput::KeyCtrlL);
  //inputMap.MapBool(KEY::kSuperL, m_id,gainput::KeySuperL);
  //inputMap.MapBool(KEY::kAltL, m_id,gainput::KeyAltL);
  //inputMap.MapBool(KEY::kAltR, m_id,gainput::KeyAltR);
  //inputMap.MapBool(KEY::kSuperR, m_id,gainput::KeySuperR);
  //inputMap.MapBool(KEY::kMenu, m_id,gainput::KeyMenu);
  //inputMap.MapBool(KEY::kCtrlR, m_id,gainput::KeyCtrlR);
  //inputMap.MapBool(KEY::kShiftR, m_id,gainput::KeyShiftR);
}

bool
GaKeyboard::isKeyDown(const KEY::E key)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  return inputMap.GetBool(key);
}


//void 
//GaKeyboard::map(const String& name, const KEY::E key)
//{
//  
//
//  inputMap.MapBool(, m_id, );
//}

}

