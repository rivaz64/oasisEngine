/**
* @file oaLoader.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/14/2021
*/

#include "oaLoader.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <stdlib.h>
#include <freeimage\FreeImage.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image\stb_image.h>
//#include "oaMesh.h"
#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaMaterial.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"
#include "oaLogger.h"
#include "oaImage.h"
#include "oaTexture.h"
#include "oaGraphicAPI.h"
#include "oaAudioAPI.h"
#include "oaSound.h"
#include "oaStaticMeshComponent.h"
#include "oaActor.h"
#include "oaStaticMesh.h"
#include "oaSkeletalMesh.h"
#include "oaSkeletalModel.h"
#include "oaSkeletalMeshComponent.h"

using Assimp::Importer;

namespace oaEngineSDK {

inline GBUFFER_FLAGS::E operator | (GBUFFER_FLAGS::E lhs, GBUFFER_FLAGS::E rhs)
{
    return static_cast<GBUFFER_FLAGS::E>(static_cast<uint8>(lhs) | 
                                         static_cast<uint8>(rhs));
}

inline GBUFFER_FLAGS::E& operator |= (GBUFFER_FLAGS::E& lhs, GBUFFER_FLAGS::E rhs)
{
    lhs = lhs | rhs;
    return lhs;
}



void
loadSkeleton(aiNode* node,SPtr<SkeletalNode> sNode,SPtr<Skeleton> skeleton)
{

  //sNode->name = ;
  
  print(node->mName.C_Str());

  sNode->transform = reinterpret_cast<Matrix4f*>(&node->mTransformation)->transposed();

  skeleton->addBone(sNode,node->mName.C_Str());//m_boneMaping.insert({sNode->name,sNode->transform});

  sNode->childs.resize(node->mNumChildren);
  for(uint32 i = 0; i < node->mNumChildren; ++i){
    sNode->childs[i] = makeSPtr<SkeletalNode>();
    sNode->childs[i]->parent = sNode;
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}

void
readStaticMesh(SPtr<Material> material,SPtr<Actor> actor, aiMesh* aMesh){
  auto mesh = makeSPtr<StaticMesh>();
  mesh->setVertexNum(static_cast<SIZE_T>(aMesh->mNumVertices));

  auto& vertices = mesh->getVertex();

  for(SIZE_T numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){

    auto& actualVertex = vertices[numVertex];

    actualVertex.location.x = aMesh->mVertices[numVertex].x;
    actualVertex.location.y = aMesh->mVertices[numVertex].y;
    actualVertex.location.z = aMesh->mVertices[numVertex].z;

    actualVertex.normal.x = aMesh->mNormals[numVertex].x;
    actualVertex.normal.y = aMesh->mNormals[numVertex].y;
    actualVertex.normal.z = aMesh->mNormals[numVertex].z;
    actualVertex.normal.w = 0;
    
    actualVertex.tangent.x = aMesh->mTangents[numVertex].x;
    actualVertex.tangent.y = aMesh->mTangents[numVertex].y;
    actualVertex.tangent.z = aMesh->mTangents[numVertex].z;
    actualVertex.tangent.w = 0;
    
    actualVertex.bitangent.x = aMesh->mBitangents[numVertex].x;
    actualVertex.bitangent.y = aMesh->mBitangents[numVertex].y;
    actualVertex.bitangent.z = aMesh->mBitangents[numVertex].z;
    actualVertex.bitangent.w = 0;

    if(aMesh->HasTextureCoords(0)){
      actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
      actualVertex.textureCord.y = 1-aMesh->mTextureCoords[0][numVertex].y;
    }
  }
  uint32 numIndices = aMesh->mNumFaces * 3;
  mesh->setIndexNum(numIndices);

  for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
  {
    aiFace* face = &aMesh->mFaces[t];
    uint32 numIndice = t*3;

    mesh->setIndexAt(numIndice,face->mIndices[0]);
    mesh->setIndexAt(numIndice+1,face->mIndices[1]);
    mesh->setIndexAt(numIndice+2,face->mIndices[2]);
  }
  //ResoureManager::instance().m_meshes.insert({model->getName()})
  mesh->writeBuffers();
  auto model = makeSPtr<Model>();
  model->setMesh(mesh);
  model->setMaterial(material);
  ResoureManager::instance().registerResourse(aMesh->mName.C_Str(),mesh);
  ResoureManager::instance().registerResourse("m_"+String(aMesh->mName.C_Str()),model);

  auto component = makeSPtr<StaticMeshComponent>();
  component->setModel(model);
  actor->attachComponent(component);
}

void
readSkeletalMesh(SPtr<Material> material,SPtr<SkeletalModel> model, aiMesh* aMesh, const String& name){

  auto& resourceManager = ResoureManager::instance();

  auto mesh = makeSPtr<SkeletalMesh>();

  auto skeleton = cast<Skeleton>(resourceManager.getResourse(String("s_")+name)).lock();

  auto& bones = mesh->getBones();

  auto smesh = mesh.get();

  smesh->setVertexNum(static_cast<SIZE_T>(aMesh->mNumVertices));

  auto& vertices = mesh->getVertex();

  vertices.resize( aMesh->mNumVertices);
  for(SIZE_T numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
    auto& actualVertex = vertices[numVertex];

    actualVertex.location.x = aMesh->mVertices[numVertex].x;
    actualVertex.location.y = aMesh->mVertices[numVertex].y;
    actualVertex.location.z = aMesh->mVertices[numVertex].z;

    actualVertex.normal.x = aMesh->mNormals[numVertex].x;
    actualVertex.normal.y = aMesh->mNormals[numVertex].y;
    actualVertex.normal.z = aMesh->mNormals[numVertex].z;
    
    actualVertex.tangent.x = aMesh->mTangents[numVertex].x;
    actualVertex.tangent.y = aMesh->mTangents[numVertex].y;
    actualVertex.tangent.z = aMesh->mTangents[numVertex].z;
    
    actualVertex.bitangent.x = aMesh->mBitangents[numVertex].x;
    actualVertex.bitangent.y = aMesh->mBitangents[numVertex].y;
    actualVertex.bitangent.z = aMesh->mBitangents[numVertex].z;

    if(aMesh->HasTextureCoords(0)){
      actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
      actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
    }
  }

  if(aMesh->HasBones()){
  
    SIZE_T bonesNum=0;
  
    for(SIZE_T boneNum = 0; boneNum < aMesh->mNumBones; ++boneNum){
  
      auto actualBone = aMesh->mBones[boneNum];
  
      String boneName = actualBone->mName.C_Str();
      
      uint32 boneId = skeleton->getBoneId(boneName);

      SIZE_T boneIndex;
  
      //bones[boneNum] = *reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix);
  
      if(!mesh->hasBone(boneId)){
        mesh->addBone(boneId,*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
        boneIndex = boneNum;
      }
      else{
        boneIndex = mesh->getBoneId(boneId);
      }

      //if(mesh->m_boneMaping.find(boneName) == mesh->m_boneMaping.end()){
      //  boneIndex = bonesNum;
      //  mesh->m_boneMaping.insert({boneName,bonesNum});
      //  //bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
      //  bones[bonesNum] = *reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix);
      //  //boneNames.push_back(boneName);
      //  ++bonesNum;
      //}
      //else{
      //
      //  boneIndex = mesh->m_boneMaping[boneName];
      //}
      //boneIndex = boneNum;
      //boneIndex = skeleton->boneMaping[boneName];
      
      //actualBone = aMesh->mBones[boneIndex];
  
      for(SIZE_T weightNum = 0; weightNum < actualBone->mNumWeights; ++weightNum){
      
        auto& actualWeight = actualBone->mWeights[weightNum];
  
        SIZE_T vertexId = actualWeight.mVertexId;
  
        auto& actualVertex = vertices[vertexId];
  
        for(uint8 i = 0; i < 4; ++i){
          if(((float*)&actualVertex.weights)[i] == 0){
            ((uint32*)&actualVertex.ids)[i] = boneIndex;
            ((float*)&actualVertex.weights)[i] = actualWeight.mWeight;
            break;
          }
        } 
      }
    }
  }

  uint32 numIndices = aMesh->mNumFaces * 3;
  mesh->setIndexNum(numIndices);

  for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
  {
    aiFace* face = &aMesh->mFaces[t];
    uint32 numIndice = t*3;

    mesh->setIndexAt(numIndice,face->mIndices[0]);
    mesh->setIndexAt(numIndice+1,face->mIndices[1]);
    mesh->setIndexAt(numIndice+2,face->mIndices[2]);
  }
  //ResoureManager::instance().m_meshes.insert({model->getName()})
  mesh->writeBuffers();
  //auto model = makeSPtr<SkeletalModel>();
  model->addMesh(mesh);
  model->addMaterial(material);
  
  
  resourceManager.registerResourse(aMesh->mName.C_Str(),mesh);
  resourceManager.registerResourse("m_"+String(aMesh->mName.C_Str()),model);
  
  model->setSkeleton(skeleton);

  model->setAnimation(cast<Animation>(resourceManager.getResourse(String("a_")+name)));

  
  //actor->attachComponent(component);
}

void 
loadMeshes(Vector<SPtr<Material>>& materials, SPtr<Actor> actor,const aiScene* loadedScene,const Path& path)
{
  auto model = makeSPtr<SkeletalModel>();
  for(uint32 numMesh = 0; numMesh < loadedScene->mNumMeshes; ++numMesh){

    auto& aMesh = loadedScene->mMeshes[numMesh];

    

    //model->addMaterial(ResoureManager::instance().m_materials["default"]);

    if(aMesh->HasBones()){
      readSkeletalMesh(materials[numMesh],model,aMesh,path.stem().string());
      
    }
    else{
      readStaticMesh(materials[numMesh],actor,aMesh);
    }

    
  }
  if(model->getNumOfMeshes() != 0){
    auto component = makeSPtr<SkeletalMeshComponent>(model);
    component->setAtTick(0);
    actor->attachComponent(component);
  }
  
}

bool
loadImage(const Path& path)
{
  if(path.extension()==L".dds"){
    if(GraphicAPI::instance().loadDDS(path)){
      return true;
    }
  }

  String s = StringUtilities::toString(path.c_str());
  int32 desiredChanels = 4;
  int32 channels = 0;
  int32 width;
  int32 height;
  uint8* pixels = stbi_load(s.c_str(),
                           &width,
                           &height,
                           &channels,
                           desiredChanels);
  if (pixels == nullptr){
    OA_WARNING_LOG(StringUtilities::toString(path.generic_wstring()) + " is an invalid image");
    return false;
  }
  auto image = makeSPtr<Image>(Vector2I(width,height),32,FORMAT::kB8G8R8A8UnormSRGB);
  image->fillFromPointer(pixels);
  if (image->getSize().x == 0 || image->getSize().y == 0){
    //OA_WARNING_LOG(path.getCompletePath() + " is an invalid image");
    return false;
  }

  //auto pitch = FreeImage_GetPitch(dib);

  //image->setName(ResoureManager::instance().getUniqueName(path.stem().generic_string()));
  image->setName(path.stem().generic_string());

  SPtr<Texture> texture = GraphicAPI::instance().createTexture();

  texture->initFromImage(image);

  texture->setPath(path);

  ResoureManager::instance().registerResourse(texture->getName(),texture);

  return true;
}

bool
loadMergedImage(const Path& path)
{
  String s = StringUtilities::toString(path.c_str());
  int32 desiredChanels = 4;
  int32 channels = 0;
  int32 width;
  int32 height;
  uint8* pixels = stbi_load(s.c_str(),
                           &width,
                           &height,
                           &channels,
                           desiredChanels);
  if (pixels == nullptr){
    OA_WARNING_LOG(StringUtilities::toString(path.generic_wstring()) + " is an invalid image");
    return false;
  }

  uint8* pixels1 = new uint8[width*height*4];
  uint8* pixels2 = new uint8[width*height*4];
  uint8* pixels3 = new uint8[width*height*4];

  for(int y = 0; y<width; ++y){
    for(int x = 0; x<width; ++x){
      uint8 v1 = pixels[y*width*4+x*4];
      uint8 v2 = pixels[y*width*4+x*4+1];
      uint8 v3 = pixels[y*width*4+x*4+2];
      pixels1[y*width*4+x*4+0] = v1;
      pixels1[y*width*4+x*4+1] = v1;
      pixels1[y*width*4+x*4+2] = v1;
      pixels2[y*width*4+x*4+0] = v2;
      pixels2[y*width*4+x*4+1] = v2;
      pixels2[y*width*4+x*4+2] = v2;
      pixels3[y*width*4+x*4+2] = v3;
      pixels3[y*width*4+x*4+1] = v3;
      pixels3[y*width*4+x*4+0] = v3;
    }
  }

  auto image1 = makeSPtr<Image>(Vector2I(width,height),32,FORMAT::kB8G8R8A8UnormSRGB);
  auto image2 = makeSPtr<Image>(Vector2I(width,height),32,FORMAT::kB8G8R8A8UnormSRGB);
  auto image3 = makeSPtr<Image>(Vector2I(width,height),32,FORMAT::kB8G8R8A8UnormSRGB);
  image1->fillFromPointer(pixels1);
  image2->fillFromPointer(pixels2);
  image3->fillFromPointer(pixels3);
  //if (image->getSize().x == 0 || image->getSize().y == 0){
  //  //OA_WARNING_LOG(path.getCompletePath() + " is an invalid image");
  //  return false;
  //}

  //auto pitch = FreeImage_GetPitch(dib);

  //image->setName(ResoureManager::instance().getUniqueName(path.stem().generic_string()));
  image1->setName(path.stem().generic_string()+"1");
  image2->setName(path.stem().generic_string()+"2");
  image3->setName(path.stem().generic_string()+"3");

  SPtr<Texture> texture1 = GraphicAPI::instance().createTexture();
  SPtr<Texture> texture2 = GraphicAPI::instance().createTexture();
  SPtr<Texture> texture3 = GraphicAPI::instance().createTexture();

  texture1->initFromImage(image1);
  texture2->initFromImage(image2);
  texture3->initFromImage(image3);


  texture1->setPath(path);
  texture2->setPath(path);
  texture3->setPath(path);

  ResoureManager::instance().registerResourse(texture1->getName(),texture1);
  ResoureManager::instance().registerResourse(texture2->getName(),texture2);
  ResoureManager::instance().registerResourse(texture3->getName(),texture3);

  delete[] pixels1;
  delete[] pixels2;
  delete[] pixels3;

  return true;
}

bool
Loader::loadTexture(const Path& path){
  return loadImage(path);
}

bool Loader::loadMergedTexture(const Path& path)
{
  return loadMergedImage(path);
}

void
tryLoadTextureChannel(aiMaterial* material, 
                      aiTextureType textureType, 
                      const Path& path,
                      const String textureChannel,
                      GBUFFER_FLAGS::E gbufferFlag,
                      GBUFFER_FLAGS::E& gbufferFlags,
                      SPtr<Material>& mat)
{
  auto& manager = ResoureManager::instance();
  aiString notMyString;
  material->Get(AI_MATKEY_TEXTURE(textureType,0),notMyString);
  if(notMyString != aiString("")){
    WString defuseName = StringUtilities::toWString(notMyString.C_Str());
    
    Path newPath;
    newPath = path.parent_path().generic_wstring();
    newPath.append(defuseName);
    auto stringName = StringUtilities::toString(newPath.stem());
    if(loadImage(newPath) /*|| 
       manager.m_textures.find(StringUtilities::getStringId(stringName)) != manager.m_textures.end()*/){

      gbufferFlags |= gbufferFlag;
      auto texture = cast<Texture>(manager.getResourse(stringName));
      if(!texture.expired())
      mat->setTexture(textureChannel, cast<Texture>(manager.getResourse(stringName)));
    }
  }
}

void
loadTextures(Vector<SPtr<Material>>& materials,const aiScene* loadedScene,const Path& path){

  auto& manager = ResoureManager::instance();

  for(uint32 numMaterial = 0; numMaterial < loadedScene->mNumMaterials; ++numMaterial){

    auto material = loadedScene->mMaterials[numMaterial];

    for(int i = 0; i<material->mNumProperties; ++i){
      auto propertie = material->mProperties[i];
      print(propertie->mKey.C_Str());
    }

    aiString notMyString;

    material->Get(AI_MATKEY_NAME,notMyString);
    
    
    WString MaterialName = StringUtilities::toWString(notMyString.C_Str());

    print(StringUtilities::toString(MaterialName));

    auto mat = makeSPtr<Material>();

    GBUFFER_FLAGS::E gbufferFlags = GBUFFER_FLAGS::kNone;

    tryLoadTextureChannel(material,
                          aiTextureType_DIFFUSE,
                          path,
                          "diffuse",
                          GBUFFER_FLAGS::kDiffuse,
                          gbufferFlags,
                          mat);

    tryLoadTextureChannel(material,
                          aiTextureType_NORMALS,
                          path,
                          "normalMap",
                          GBUFFER_FLAGS::kNormals,
                          gbufferFlags,
                          mat);
    
    tryLoadTextureChannel(material,
                          aiTextureType_SPECULAR,
                          path,
                          "specular",
                          GBUFFER_FLAGS::kSpecular,
                          gbufferFlags,
                          mat);

    //tryLoadTextureChannel(material,
    //                      aiTextureType_DIFFUSE_ROUGHNESS,
    //                      path,
    //                      "roughtness",
    //                      GBUFFER_FLAGS::kRoughtness,
    //                      gbufferFlags,
    //                      mat);
    
    //print("looking for textures");
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT_OCCLUSION,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_BASE_COLOR,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_CLEARCOAT,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE_ROUGHNESS,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_DISPLACEMENT,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSION_COLOR,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_EMISSIVE,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_LIGHTMAP,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_METALNESS,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMAL_CAMERA,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_OPACITY,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_REFLECTION,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_SHEEN,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_SHININESS,0),notMyString);
    //print(notMyString.C_Str());
    //material->Get(AI_MATKEY_TEXTURE(aiTextureType_TRANSMISSION,0),notMyString);
    //print(notMyString.C_Str());
    //print("looking finish");
    print(StringUtilities::intToString(gbufferFlags));
    mat->setShader(gbufferFlags);

    materials.push_back(mat);

    mat->setName(StringUtilities::toString(MaterialName));

    manager.registerResourse(StringUtilities::toString(MaterialName),mat); 

    aiColor3D color(0.f,0.f,0.f);

    aiReturn ret = material->Get(AI_MATKEY_COLOR_DIFFUSE,color);

    if(ret == aiReturn_SUCCESS){
      mat->setColor("diffuse",Color(color.r,color.g,color.b));
      print(StringUtilities::floatToString(color.r) + " " + StringUtilities::floatToString(color.g) + " " + StringUtilities::floatToString(color.b) + " " );
    }
    
  }

}

//void
//loadMaterial()

void 
loadSkeletons(const aiScene* loadedScene,const Path& path)
{
  auto& manager = ResoureManager::instance();

  auto skeleton = makeSPtr<Skeleton>();

  skeleton->m_skeleton = makeSPtr<SkeletalNode>();

  skeleton->m_globalInverse = 
    reinterpret_cast<Matrix4f*>(&loadedScene->mRootNode->mTransformation)->inverse();

  loadSkeleton(loadedScene->mRootNode,skeleton->m_skeleton,skeleton);

  manager.registerResourse(String("s_")+path.stem().string(),skeleton);
}

void 
loadAnimations(const aiScene* loadedScene,const Path& path)
{
  const aiScene* scene = static_cast<const aiScene*>(loadedScene);

  auto& manager = ResoureManager::instance();

  auto skeleton = cast<Skeleton>(manager.getResourse(String("s_")+path.stem().string()).lock());

  for(uint32 animNum = 0; animNum < scene->mNumAnimations; ++animNum){

    auto actualAnim = scene->mAnimations[animNum];
   
    auto animation = makeSPtr<Animation>();
   
    animation->setDuration(static_cast<float>(actualAnim->mDuration));
   
    animation->setTicksPerSecond(static_cast<float>(actualAnim->mTicksPerSecond));
   
    for(uint32 numChannel = 0; numChannel < actualAnim->mNumChannels; ++numChannel){
      
      auto actualChannel = actualAnim->mChannels[numChannel];
   
      auto node = makeSPtr<AnimChannel>();
   
      //node->name = actualChannel->mNodeName.C_Str();
   
      node->locations.resize(actualChannel->mNumPositionKeys);
      print(StringUtilities::floatToString(actualChannel->mNumPositionKeys));
   
      for(uint32 i = 0; i < actualChannel->mNumPositionKeys; ++i){
        Vector4f pos; 
        pos.x = actualChannel->mPositionKeys[i].mValue.x;
        pos.y = actualChannel->mPositionKeys[i].mValue.y;
        pos.z = actualChannel->mPositionKeys[i].mValue.z;
        pos.z = 0;
        node->locations[i] = 
        {static_cast<float>(actualChannel->mPositionKeys[i].mTime),
        pos};

      }
   
      node->scales.resize(actualChannel->mNumScalingKeys);
      print(StringUtilities::floatToString(actualChannel->mNumScalingKeys));
   
      for(uint32 i = 0; i < actualChannel->mNumScalingKeys; ++i){
        Vector4f sca; 
        sca.x = actualChannel->mScalingKeys[i].mValue.x;
        sca.y = actualChannel->mScalingKeys[i].mValue.y;
        sca.z = actualChannel->mScalingKeys[i].mValue.z;
        sca.z = 0;
        node->scales[i] =
        {static_cast<float>(actualChannel->mScalingKeys[i].mTime),
        sca};
      }
   
      node->rotations.resize(actualChannel->mNumRotationKeys);
      print(StringUtilities::floatToString(actualChannel->mNumRotationKeys));
   
      for(uint32 i = 0; i < actualChannel->mNumRotationKeys; ++i){
        Quaternion q;
   
        q.i = actualChannel->mRotationKeys[i].mValue.x;
        q.j = actualChannel->mRotationKeys[i].mValue.y;
        q.k = actualChannel->mRotationKeys[i].mValue.z;
        q.r = actualChannel->mRotationKeys[i].mValue.w;
   
        auto asMat = actualChannel->mRotationKeys[i].mValue.GetMatrix();
   
        auto oaMat = q.toMatrix();
   
        node->rotations[i] = 
        {static_cast<float>(actualChannel->mRotationKeys[i].mTime),q};
      }
   
      animation->addChannel(skeleton->getBoneId(actualChannel->mNodeName.C_Str()),node);
      print("");
    }
   
    ResoureManager::instance().registerResourse("a_"+path.stem().string(),animation);
  }
}


void
Loader::load(LOADERFLAGS::E /*flags*/)
{
/*
  auto model = makeSPtr<Model>();
  if(flags & LOADERFLAGS::kMesh){
    loadMeshes(model);
  }
  if(flags & LOADERFLAGS::kTexture){
    loadTextures(model);
  }
  if(flags & LOADERFLAGS::kSkeleton){
    loadSkeletons();
  }
  if(flags & LOADERFLAGS::kAnimation){
    loadAnimations();
  }
  ResoureManager::instance().m_models.insert({m_file.getCompletePath(),model});
  model->m_name = m_file.getName();
  */
}

bool//LOADERFLAGS::E
Loader::loadScene(const Path& file,WPtr<Actor> wActor)
{
  auto flags = aiProcess_Triangulate | 
               //aiProcess_GenNormals |
               aiProcess_GenSmoothNormals | 
               aiProcess_OptimizeMeshes | 
               aiProcess_OptimizeGraph |
               aiProcess_CalcTangentSpace;
  Importer importer;

  String completePath = StringUtilities::toString(file.c_str());

  const aiScene* importedScene = importer.ReadFile(completePath.c_str(),flags);
  
  if(wActor.expired()) return true;
  auto actor = wActor.lock();

  //auto model = makeSPtr<Model>();
  Vector<SPtr<Model>> models;
  if(!importedScene){
    //OA_DEBUG_LOG("file "+completePath+"not found");
    //__PRETTY_FUNCTION__;
    return false;//static_cast<LOADERFLAGS::E>(m_loadedFlags);
  }
  Vector<SPtr<Material>> materials;
  if(importedScene->HasMaterials()){
    m_loadedFlags |= LOADERFLAGS::kTexture;
    loadTextures(materials,importedScene,file);
  }

  if(importedScene->HasAnimations()){
    loadSkeletons(importedScene,file);
    loadAnimations(importedScene,file);
    //m_loadedFlags |= LOADERFLAGS::kAnimation | LOADERFLAGS::kSkeleton;
  }   

  if(importedScene->HasMeshes()){
    m_loadedFlags |= LOADERFLAGS::kMesh;
    loadMeshes(materials,actor,importedScene,file);
  }

  //ResoureManager::instance().registerResourse(file.stem().generic_string(),model); 
  //model->setName(file.stem().generic_string());

  return true;//static_cast<LOADERFLAGS::E>(m_loadedFlags);
}

bool
Loader::loadResource(const Path & path,WPtr<Actor> actor)
{
  auto extencion = StringUtilities::toString(path.extension());
  if(extencion == ".png" || extencion == ".jpg"){
    return loadTexture(path);
  }

  if(extencion == ".obj" || extencion == ".fbx"){
    return loadScene(path,actor);
  }

  if(extencion == ".wav"){
    loadSound(path);
  }

  return false;
}

bool 
Loader::loadSound(const Path & path)
{
  auto& audioApi = AudioAPI::instance();
  auto sound = audioApi.createSound();
  if(!sound->loadFromFile(path)){
    return false;
  }
  auto name = StringUtilities::toString(path.filename());
  sound->setName(name);
  ResoureManager::instance().registerResourse(name,sound);  
  return true;
}

}