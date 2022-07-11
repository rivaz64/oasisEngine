#include "oaSerializer.h"
#include "oaPath.h"
//#include "oaModel.h"
//#include "oaPath.h"
//#include "oaMesh.h"
//#include "oaStaticMesh.h"
//#include "oaResoureManager.h"
//#include "oaMaterial.h"
//#include "oaImage.h"
//#include "oaTexture.h"
//#include "oaResoureManager.h"
//#include "oaShaderProgram.h"
//#include "oaActor.h"

namespace oaEngineSDK{

bool
Serializer::init(const Path& path,bool write)
{
  int flags;
  String firm;
  if(write){
    flags = fstream::out | ios::binary;
    firm = "oasisFile";
    file.open(StringUtilities::toString(path.getCompletePath()),flags);
    file.write(firm.c_str(),firm.size()*sizeof(char));
  }
  else{
    flags = fstream::in | ios::binary;
    firm.resize(9);
    SIZE_T nameData = reinterpret_cast<SIZE_T>(firm.data());
    file.open(StringUtilities::toString(path.getCompletePath()),flags);
    file.read(reinterpret_cast<char*>(nameData),sizeof(char)*9);
    if(firm != "oasisFile"){
      return false;
    }
  }

  return true;
}

void 
Serializer::encodeNumber(SIZE_T number)
{
  file.write(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
}

SIZE_T
Serializer::decodeNumber()
{
  SIZE_T number;
  file.read(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
  return number;
}

void
Serializer::encodeString(const String& string)
{
  SIZE_T nameSize = string.size();

  file.write(reinterpret_cast<char*>(&nameSize),sizeof(SIZE_T));
  file.write(string.c_str(),nameSize);
}

String 
Serializer::decodeString() 
{
  String string;
  SIZE_T nameSize;

  file.read(reinterpret_cast<char*>(&nameSize),sizeof(SIZE_T));
  string.resize(nameSize);

  SIZE_T nameData = reinterpret_cast<SIZE_T>(string.data());
  file.read(reinterpret_cast<char*>(nameData),sizeof(char)*nameSize);

  return string;
}
//
//SPtr<Actor> 
//Serializer::decodeActor()
//{
//  auto actor = makeSPtr<Actor>();
//
//  actor->setName(decodeString());
//
//  auto& transform = actor->GetActorTransform();
//  file.read(reinterpret_cast<char*>(&transform),sizeof(Vector3f)*3);
//
//  return actor;
//}


}

