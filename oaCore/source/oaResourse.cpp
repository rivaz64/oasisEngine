#include "oaResourse.h"

namespace oaEngineSDK
{

void Resourse::save(Serializer& serializer)
{
  Path finalPath = serializer.m_path.string()+"/"+getName()+".oa";

  serializer.encodeNumber(getType());
  serializer.encodeString(finalPath.string());

  Serializer localSerializer;
  localSerializer.init(finalPath,true);

  onSave(localSerializer);
}

}

