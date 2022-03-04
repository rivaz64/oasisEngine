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

namespace oaEngineSDK{



void
Serializer::init(const Path& path)
{
  file.open(StringUtilities::toString(path.getCompletePath()),std::fstream::out | std::fstream::in | std::ios::binary);
}

void 
Serializer::encodeNumber(SIZE_T n)
{
  file.write(reinterpret_cast<char*>(&n),sizeof(SIZE_T));
}

SIZE_T Serializer::decodeNumber()
{
  SIZE_T number;
  file.read(reinterpret_cast<char*>(&number),sizeof(SIZE_T));
  return number;
}

void
Serializer::encodeString(const String& string)
{
  uint32 nameSize = string.size();

  file.write(reinterpret_cast<char*>(&nameSize),sizeof(int32));
  file.write(string.c_str(),nameSize);
}

String 
Serializer::decodeString()
{
  String string;
  uint32 nameSize;

  file.read(reinterpret_cast<char*>(&nameSize),sizeof(int32));
  string.resize(nameSize);

   SIZE_T nameData = reinterpret_cast<SIZE_T>(string.data());
  file.read(reinterpret_cast<char*>(nameData),sizeof(char)*nameSize);

  return string;
}

void 
Serializer::encodeImage(SPtr<Image> image)
{
  encodeString(image->getName());

  file.write(reinterpret_cast<char*>(&image->m_width),sizeof(int32));
  file.write(reinterpret_cast<char*>(&image->m_height),sizeof(int32));
  file.write(reinterpret_cast<char*>(&image->m_pitch),sizeof(int32));
  file.write(reinterpret_cast<char*>(&image->m_format),sizeof(int32));
  file.write(reinterpret_cast<char*>(image->m_pixels),sizeof(int32)*image->m_width*image->m_height);
}

SPtr<Image> 
Serializer::decodeImage()
{
  auto image = newSPtr<Image>();

  image->setName(decodeString());

  file.read(reinterpret_cast<char*>(&image->m_width),sizeof(int32));
  file.read(reinterpret_cast<char*>(&image->m_height),sizeof(int32));
  file.read(reinterpret_cast<char*>(&image->m_pitch),sizeof(int32));
  file.read(reinterpret_cast<char*>(&image->m_format),sizeof(int32));

  uint32 imageSize = image->m_height*image->m_pitch;

  image->m_pixels = new uint8[imageSize];

  file.read(reinterpret_cast<char*>(image->m_pixels),imageSize);

  return image;
}

void 
Serializer::encodeMaterial(SPtr<Material> material)
{
  encodeString(material->getName());

  auto shader = material->getShader();

  file.write(reinterpret_cast<char*>(&shader),sizeof(SHADER_TYPE::E));

  auto types = material->getTextureTypes();

  SIZE_T numOfTypes = types.size();

  file.write(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  SIZE_T nameSize;

  for(auto& type : types){
    file.write(reinterpret_cast<char*>(&type),sizeof(TEXTURE_TYPE::E));
    encodeString(material->getTexture(type)->getName());
  }

}

SPtr<Material> 
Serializer::decodeMaterial()
{
  auto& resourseManager = ResoureManager::instance();

  auto material = newSPtr<Material>();

  material->setName(decodeString());

  SHADER_TYPE::E shader;

  file.read(reinterpret_cast<char*>(&shader),sizeof(SHADER_TYPE::E));

  material->setShader(shader);

  SIZE_T numOfTypes;

  file.read(reinterpret_cast<char*>(&numOfTypes),sizeof(SIZE_T));

  TEXTURE_TYPE::E type;

  String name;

  for(SIZE_T typeNum = 0; typeNum<numOfTypes; ++typeNum){
    file.read(reinterpret_cast<char*>(&type),sizeof(TEXTURE_TYPE::E));
    material->setTexture(type, resourseManager.m_textures[decodeString()]);
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

    auto vertexData = staticMesh->getVertex().data();

    file.write(reinterpret_cast<const char*>(vertexData),sizeof(Vertex)*vertexNum);

    encodeString(model->getMaterial(meshN)->getName());
  }
}

SPtr<Model> 
Serializer::decodeModel()
{
  auto model = newSPtr<Model>();

  model->setName(decodeString());

  SIZE_T meshNum;

  file.read(reinterpret_cast<char*>(&meshNum),sizeof(SIZE_T));

  //model->setNumOfMeshes(meshNum);

  SIZE_T indexNum;

  String materialName;

  for(SIZE_T meshN = 0; meshN < meshNum; meshN++){
    auto mesh = newSPtr<StaticMesh>();

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

}

