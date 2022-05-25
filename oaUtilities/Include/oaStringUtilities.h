/**
 * @file oaStringUtilities.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 2/16/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
//#include "oaVector3f.h"

namespace oaEngineSDK{

/**
 * @brief class for everything string related
*/
class OA_UTILITY_EXPORT StringUtilities
{


 public:
  /**
   * @brief changes something to string
   * @tparam T the tipe of the argument
   * @return the string
  */
  static FORCEINLINE String
  intToString(int32 param){
    return to_string(param);
  }

  static FORCEINLINE String
  floatToString(float param){
    return to_string(param);
  }

  static FORCEINLINE String
  vector4ToString(const Vector4f& param);

  static FORCEINLINE WString
  toWString(const String& string){
    return WString(string.begin(),string.end());
  }

  static String
  toString(const WString& string);

  static uint32
  getStringId(const String&);


};

}



