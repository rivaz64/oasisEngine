/**
* @file oaImage.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/12/2021
*/

#include "oaImage.h"
#include "oaSerializer.h"

namespace oaEngineSDK
{
RESOURSE_TYPE::E
Image::getType()
{
  return RESOURSE_TYPE::kImage;
}
void
Image::save(Serializer& serializer)
{
  Path finalPath = serializer.m_path.string()+"/"+getName()+".oa";

  serializer.encodeNumber(getType());
  serializer.encodeString(finalPath.string());

  Serializer localSerializer;
  localSerializer.init(finalPath,true);

  localSerializer.file.write(reinterpret_cast<const char*>(&getSize()),
                        sizeof(Vector2I)+sizeof(int32)+sizeof(FORMAT::E));

  localSerializer.file.write(reinterpret_cast<const char*>(getPixels()),
                        getNumberOfBytes());
}

void 
Image::load(Serializer& serializer)
{
  //setName(serializer.decodeString());

  serializer.file.read(reinterpret_cast<char*>(&m_size),
                       sizeof(Vector2I)+sizeof(int32)+sizeof(FORMAT::E));
  init();
  serializer.file.read(reinterpret_cast<char*>(unconstPointer(m_pixels.data())),
                       getNumberOfBytes());
}

}