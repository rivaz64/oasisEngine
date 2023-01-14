/**
* @file oaSerializer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaColor.h"
//#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief encodes and decodes files to binary
*/
class OA_UTILITY_EXPORT Serializer
{
 public:

  FORCEINLINE void setPath(const Path& path)
  {
    m_path = path;
  }

  bool 
  open(Path path,bool write);

  /**
   * @brief initializes a serializer for a resource
   * @param path the path to read/write
   * @param write true for writing, false for reading
   * @return if all worked correctly
  */
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

  void
  encodeColor(const Color& color);

  Color
  decodeColor(); 

  void
  encodeTransform(const Transform& transform);

  Transform
  decodeTransform();


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

  template<class K,class T>
  void 
  encodeMap(const Map<K,T>& map)
  {
    auto size = map.size();
    encodeSize(size);
    for(auto it = map.begin(); it != map.end(); ++it){
      file.write(reinterpret_cast<const char*>(&(*it)),sizeof(Pair<K,T>));
    }
  }

  template<class K,class T>
  void
  decodeMap(Map<K,T>& map)
  {
    SIZE_T num;
    num = decodeSize();
    for(SIZE_T i = 0; i<num; ++i){
      Pair<K,T> par;
      file.read(reinterpret_cast<char*>(&par),sizeof(Pair<K,T>));
      map.insert(par);
    }
  }

  FStream file;

  Path m_path;
};

}
