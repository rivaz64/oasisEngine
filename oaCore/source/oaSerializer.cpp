#include "oaSerializer.h"
#include "oaModel.h"
#include "oaPath.h"
#include "oaMesh.h"
#include "oaStaticMesh.h"
#include "oaResoureManager.h"
#include "oaMaterial.h"
#include "oaImage.h"
#include "oaTexture.h"
#include "oaResoureManager.h"
#include "oaShaderProgram.h"
#include "oaActor.h"

namespace oaEngineSDK{

bool
Serializer::init(const Path& path,FILE::E flag)
{
  int flags;
  String firm;
  if(flag == FILE::kWrite){
    flags = fstream::out | ios::binary;
    firm = "oasisFile";
    file.open(StringUtilities::toString(path.getCompletePath()),flags);
    file.write(firm.c_str(),firm.size()*sizeof(char));
  }
  else if(flag == FILE::kRead){
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

void 
Serializer::encodeImage(SPtr<Image> image)
{
  encodeString(image->getName());

  file.write(reinterpret_cast<const char*>(&image->getSize()),
             sizeof(Vector2I)+sizeof(int32)+sizeof(FORMAT::E));

  file.write(reinterpret_cast<const char*>(image->getPixels()),
             image->getNumberOfBytes());
}

SPtr<Image> 
Serializer::decodeImage()
{
  auto image = makeSPtr<Image>();

  image->setName(decodeString());

  file.read(reinterpret_cast<char*>(unconstPointer(&image->getSize())),
            sizeof(Vector2I)+sizeof(int32)+sizeof(FORMAT::E));

  image->init();

  file.read(reinterpret_cast<char*>(unconstPointer(image->getPixels())),
             image->getNumberOfBytes());

  return image;
}

void 
Serializer::encodeMaterial(SPtr<Material> material)
{
  encodeString(material->getName());

  encodeNumber(material->getShader());

  auto types = material->getTextureChannels();

  SIZE_T numOfTypes = types.size();

  file.write(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  for(auto& type : types){
    encodeString(type);
    encodeString(material->getTexture(type)->getName());
  }
}

SPtr<Material> 
Serializer::decodeMaterial()
{
  auto& resourseManager = ResoureManager::instance();

  auto material = makeSPtr<Material>();

  material->setName(decodeString());

  material->setShader(decodeNumber());

  SIZE_T numOfTypes;

  file.read(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  String channel, name;

  for(SIZE_T typeNum = 0; typeNum<numOfTypes; ++typeNum){
    channel = decodeString();
    name =  decodeString();
    material->setTexture(channel, resourseManager.m_textures[name]);
  }

  resourseManager.m_materials.insert({material->getName(),material});

  return material;
}



void
Serializer::encodeModel(SPtr<Model> model)
{
  encodeString(model->getName());

  SIZE_T meshNum = model->getNumOfMeshes();

  file.write(reinterpret_cast<char*>(&meshNum),sizeof(SIZE_T));

  for(SIZE_T meshN = 0; meshN < meshNum; meshN++){

    auto& mesh = model->getMesh(meshN);

    SIZE_T indexNum = mesh->getIndexNum();

    file.write(reinterpret_cast<char*>(&indexNum),sizeof(SIZE_T));

    auto indexData = mesh->getIndex().data();

    file.write(reinterpret_cast<const char*>(indexData),sizeof(uint32)*indexNum);

    auto staticMesh = cast<StaticMesh>(mesh);

    SIZE_T vertexNum = staticMesh->getVertexNum();

    file.write(reinterpret_cast<char*>(&vertexNum),sizeof(SIZE_T));

    auto vertices = staticMesh->getVertex();
    auto vertexData = vertices.data();

    file.write(reinterpret_cast<const char*>(vertexData),sizeof(Vertex)*vertexNum);

    auto matName = model->getMaterial(meshN)->getName();
    if(matName != "")
    encodeString(matName);
  }
}

SPtr<Model> 
Serializer::decodeModel()
{
  auto model = makeSPtr<Model>();

  model->setName(decodeString());

  SIZE_T meshNum;

  file.read(reinterpret_cast<char*>(&meshNum),sizeof(SIZE_T));

  //model->setNumOfMeshes(meshNum);

  SIZE_T indexNum;

  String materialName;

  for(SIZE_T meshN = 0; meshN < meshNum; meshN++){
    auto mesh = makeSPtr<StaticMesh>();

    file.read(reinterpret_cast<char*>(&indexNum),sizeof(SIZE_T));

    mesh->setIndexNum(indexNum);

    SIZE_T indexData = reinterpret_cast<SIZE_T>(mesh->getIndex().data());

    file.read(reinterpret_cast<char*>(indexData),sizeof(uint32)*indexNum);

    //auto staticMesh = cast<StaticMesh>(mesh);

    SIZE_T vertexNum = mesh->getVertexNum();

    file.read(reinterpret_cast<char*>(&vertexNum),sizeof(SIZE_T));

    mesh->setVertexNum(vertexNum);

    SIZE_T vertexData = reinterpret_cast<SIZE_T>(mesh->getVertex().data());

    file.read(reinterpret_cast<char*>(vertexData),sizeof(Vertex)*vertexNum);

    mesh->create();

    model->addMesh(mesh);

    materialName = decodeString();

    model->addMaterial(ResoureManager::instance().m_materials[materialName]);
  }
  
  return model;
}

void 
Serializer::encodeActor(SPtr<Actor> actor)
{
  encodeString(actor->getName());
  auto& transform = actor->GetActorTransform();
  file.write(reinterpret_cast<const char*>(&transform),sizeof(Vector3f)*3);
}

SPtr<Actor> 
Serializer::decodeActor()
{
  auto actor = makeSPtr<Actor>();

  actor->setName(decodeString());

  auto& transform = actor->GetActorTransform();
  file.read(reinterpret_cast<char*>(&transform),sizeof(Vector3f)*3);

  return actor;
}


}

