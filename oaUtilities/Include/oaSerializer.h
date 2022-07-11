/**
* @file oaSerializer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
//#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief encodes and decodes files to binary
*/
class OA_UTILITY_EXPORT Serializer
{
 public:

  bool 
  init(const Path& path,bool write);

  void
  encodeNumber(SIZE_T n);

  SIZE_T
  decodeNumber();

  void
  encodeString(const String& string);

  String
  decodeString();
 //
 //void
 //encodeActor(WPtr<Actor> actor);
 //
 //WPtr<Actor>
 //decodeActor();

  FStream file;
};

}
