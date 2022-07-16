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
  encodeNumber(int32 number);

  int32
  decodeNumber();

  void
  encodeSize(SIZE_T size);

  SIZE_T
  decodeSize();

  void
  encodeString(const String& string);

  String
  decodeString();

  template<class T>
  void 
  encodeVector(const Vector<T>& vector)
  {
    auto size = vector.size();
    encodeSize(size);
    file.write(reinterpret_cast<const char*>(vector.data()),
                          sizeof(T)*vector.size());
  }

  template<class T>
  void
  decodeVector(Vector<T>& vector)
  {
    SIZE_T num;
    num = decodeSize();
    vector.resize(num);
    file.read(reinterpret_cast<char*>(vector.data()),
              sizeof(T)*num);
  }
 //
 //void
 //encodeActor(WPtr<Actor> actor);
 //
 //WPtr<Actor>
 //decodeActor();

  FStream file;
};

}
