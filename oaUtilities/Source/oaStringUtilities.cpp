#include "oaStringUtilities.h"
#include "oaVector4f.h"
namespace oaEngineSDK{

using std::locale;
using std::ctype;
using std::use_facet;

template<typename T>
T
UTF8To32(T begin, T end, char32_t& output, char32_t invalidChar = 0) {
  //Nothing to parse
  if (begin >= end) {
    return begin;
  }

  //Determine the number of bytes used by the character
  uint32 numBytes;

  uint8 firstByte = static_cast<uint8>(*begin);
  if (192 > firstByte) {
    numBytes = 1;
  }
  else if (224 > firstByte) {
    numBytes = 2;
  }
  else if (240 > firstByte) {
    numBytes = 3;
  }
  else if (248 > firstByte) {
    numBytes = 4;
  }
  else if (252 > firstByte) {
    numBytes = 5;
  }
  else {// < 256
    numBytes = 6;
  }

  //Not enough bytes were provided, invalid character
  if ((begin + numBytes) > end) {
    output = invalidChar;
    return end;
  }

  //Decode the character
  output = 0;
  switch (numBytes)
  {
    case 6: output += static_cast<uint8>(*begin); ++begin; output <<= 6; 
    case 5: output += static_cast<uint8>(*begin); ++begin; output <<= 6; 
    case 4: output += static_cast<uint8>(*begin); ++begin; output <<= 6; 
    case 3: output += static_cast<uint8>(*begin); ++begin; output <<= 6; 
    case 2: output += static_cast<uint8>(*begin); ++begin; output <<= 6; 
    case 1: output += static_cast<uint8>(*begin); ++begin; 
    default: break;
  }

  constexpr uint32 offsets[6] = { 0x00000000,
                                  0x00003080,
                                  0x000E2080,
                                  0x03C82080,
                                  0xFA082080,
                                  0x82082080 };
  output -= offsets[numBytes - 1];
  return begin;
}

char
UTF32ToANSI(char32_t input,
            char invalidChar = 0,
            const locale& local = locale("")) {
  const ctype<wchar_t>& facet = use_facet<ctype<wchar_t>>(local);

  //Note: Same as above, not exactly correct as narrow() doesn't accept a surrogate pair
  return facet.narrow((wchar_t)input, invalidChar);
}

String 
StringUtilities::toString(const WString& string)
{
  String output;

  auto iter = string.begin();
  while (iter != string.end()) {
    char32_t u32char = 0;
    iter = UTF8To32(iter, string.end(), u32char,0);
    output.push_back(UTF32ToANSI(u32char));
  }

  return output;
}

String
StringUtilities::vector4ToString(const Vector4f& param){
  return floatToString(param.x)+", "+
         floatToString(param.y)+", "+
         floatToString(param.z)+", "+
         floatToString(param.w);
}

}

