#include "oaSerializer.h"

namespace oaEngineSDK{

bool Serializer::open(Path path,bool write)
{
  //int flags;
  //String firm;
  //auto finalPath = m_path;
  //finalPath += path;
  //if(write){
  //  flags = fstream::out | ios::binary;
  //  firm = "oasisFile";
  //  file.open((m_path+path).c_str(),flags);
  //  file.write(firm.c_str(),firm.size()*sizeof(char));
  //}
  //else{
  //  flags = fstream::in | ios::binary;
  //  firm.resize(9);
  //  SIZE_T nameData = reinterpret_cast<SIZE_T>(firm.data());
  //  file.open(path.c_str(),flags);
  //  file.read(reinterpret_cast<char*>(nameData),sizeof(char)*9);
  //  if(firm != "oasisFile"){
  //    return false;
  //  }
  //}

  return true;
}

bool
Serializer::init(const Path& path,bool write)
{
  int flags;
  String firm;
  m_path = path.parent_path().string();
  if(write){
    flags = fstream::out | ios::binary;
    firm = "oasisFile";
    file.open(path.c_str(),flags);
    file.write(firm.c_str(),firm.size()*sizeof(char));
  }
  else{
    flags = fstream::in | ios::binary;
    firm.resize(9);
    SIZE_T nameData = reinterpret_cast<SIZE_T>(firm.data());
    file.open(path.c_str(),flags);
    file.read(reinterpret_cast<char*>(nameData),sizeof(char)*9);
    if(firm != "oasisFile"){
      return false;
    }
  }

  return true;
}

void
Serializer::encodeNumber(int32 number)
{
  file.write(reinterpret_cast<char*>(&number),sizeof(int32));
}

int32
Serializer::decodeNumber()
{
  int32 number;
  file.read(reinterpret_cast<char*>(&number),sizeof(int32));
  return number;
}

void 
Serializer::encodeSize(SIZE_T size)
{
  file.write(reinterpret_cast<char*>(&size),sizeof(SIZE_T));
}

SIZE_T Serializer::decodeSize()
{
  SIZE_T number;
  file.read(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
  return number;
}

//void 
//Serializer::encodeNumber(SIZE_T number)
//{
//  file.write(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
//}
//
//SIZE_T
//Serializer::decodeNumber()
//{
//  SIZE_T number;
//  file.read(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
//  return number;
//}

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

void 
Serializer::encodeColor(const Color& color)
{
  file.write(reinterpret_cast<const char*>(&color.r),sizeof(Color));
}

Color
Serializer::decodeColor()
{
  Color color;
  file.read(reinterpret_cast<char*>(&color.r),sizeof(Color));
  return color;
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

