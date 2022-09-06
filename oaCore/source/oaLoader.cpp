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
#include "oaMesh.h"
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

  sNode->name = node->mName.C_Str();
  
  print(node->mName.C_Str());

  sNode->transform = reinterpret_cast<Matrix4f*>(&node->mTransformation)->transposed();

  skeleton->m_boneMaping.insert({sNode->name,sNode->transform});

  sNode->childs.resize(node->mNumChildren);
  for(uint32 i = 0; i < node->mNumChildren; ++i){
    sNode->childs[i] = makeSPtr<SkeletalNode>();
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}

void
readStaticMesh(SPtr<StaticMesh> mesh, aiMesh* aMesh){
  
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
}

//void
//readSkeletalMesh(SPtr<Mesh<AnimationVertex>> mesh, aiMesh* aMesh){
//
//  auto& bones = mesh->m_bones;
//
//  auto& vertices = mesh->m_vertices;
//
//  vertices.resize( aMesh->mNumVertices);
//  for(SIZE_T numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
//    auto& actualVertex = vertices[numVertex];
//
//    actualVertex.location.x = aMesh->mVertices[numVertex].x;
//    actualVertex.location.y = aMesh->mVertices[numVertex].y;
//    actualVertex.location.z = aMesh->mVertices[numVertex].z;
//
//    actualVertex.normal.x = aMesh->mNormals[numVertex].x;
//    actualVertex.normal.y = aMesh->mNormals[numVertex].y;
//    actualVertex.normal.z = aMesh->mNormals[numVertex].z;
//    
//    actualVertex.tangent.x = aMesh->mTangents[numVertex].x;
//    actualVertex.tangent.y = aMesh->mTangents[numVertex].y;
//    actualVertex.tangent.z = aMesh->mTangents[numVertex].z;
//    
//    actualVertex.bitangent.x = aMesh->mBitangents[numVertex].x;
//    actualVertex.bitangent.y = aMesh->mBitangents[numVertex].y;
//    actualVertex.bitangent.z = aMesh->mBitangents[numVertex].z;
//
//    if(aMesh->HasTextureCoords(0)){
//      actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
//      actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
//    }
//  }
//
//  if(aMesh->HasBones()){
//
//    SIZE_T bonesNum=0;
//
//    for(SIZE_T boneNum = 0; boneNum < aMesh->mNumBones; ++boneNum){
//
//      auto actualBone = aMesh->mBones[boneNum];
//
//      String boneName = actualBone->mName.C_Str();
//
//      SIZE_T boneIndex;
//
//      if(mesh->m_boneMaping.find(boneName) == mesh->m_boneMaping.end()){
//        boneIndex = bonesNum;
//        mesh->m_boneMaping.insert({boneName,bonesNum});
//        bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
//        //boneNames.push_back(boneName);
//        ++bonesNum;
//      }
//      else{
//
//        boneIndex = mesh->m_boneMaping[boneName];
//      }
//
//      //boneIndex = skeleton->boneMaping[boneName];
//
//      actualBone = aMesh->mBones[boneIndex];
//
//      for(SIZE_T weightNum = 0; weightNum < actualBone->mNumWeights; ++weightNum){
//      
//        auto& actualWeight = actualBone->mWeights[weightNum];
//
//        SIZE_T vertexId = actualWeight.mVertexId;
//
//        auto& actualVertex = vertices[vertexId];
//
//        for(uint8 i = 0; i < 8; ++i){
//          if(((float*)&actualVertex.weights)[i] == 0){
//            ((uint32*)&actualVertex.ids)[i] = boneIndex;
//            ((float*)&actualVertex.weights)[i] = actualWeight.mWeight;
//            break;
//
//          }
//        } 
//      }
//    }
//  }
//}

void 
loadMeshes(SPtr<Model> model,const aiScene* loadedScene)
{
  for(uint32 numMesh = 0; numMesh < loadedScene->mNumMeshes; ++numMesh){

    auto& aMesh = loadedScene->mMeshes[numMesh];

    auto mesh = makeSPtr<StaticMesh>();

    readStaticMesh(mesh,aMesh);

    //model->addMaterial(ResoureManager::instance().m_materials["default"]);

    /*if(aMesh->HasBones()){

    }
    else{
      readSkeletalMesh(cast<SkeletalMesh>(mesh),aMesh);
      
    }*/

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
    model->addMesh(mesh);
  }
}

bool
loadImage(const Path& path){

  if(path.extension()==L".dds"){
    if(GraphicAPI::instance().loadDDS(path)){
      return true;
    }
  }


  String s = StringUtilities::toString(path.c_str());
  //FIBITMAP* dib(0);
  //FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
  //
  //auto file = s.c_str();
  //fif = FreeImage_GetFileType(file,0);
  //
  //if (fif == FIF_UNKNOWN){
  //  
  //  fif = FreeImage_GetFIFFromFilename(file);
  //}
  //
  //if (fif == FIF_UNKNOWN){
  //  //OA_WARNING_LOG("unknown format of image"+file);
  //  return false;
  //}
  //  
  //if (FreeImage_FIFSupportsReading(fif)) {
  //  dib = FreeImage_Load(fif, file);
  //  if (!dib){
  //    //OA_WARNING_LOG("file "+path.getCompletePath() + " could not be loaded");
  //    return false;
  //  }
  //  dib = FreeImage_ConvertTo32Bits(dib);
  //}
  //
  //
  //
  // auto image = makeSPtr<Image>(Vector2I(FreeImage_GetWidth(dib),FreeImage_GetHeight(dib)),
  //                              FreeImage_GetBPP(dib),
  //                              FORMAT::kB8G8R8A8UnormSRGB);
  //
  //image->fillFromPointer(FreeImage_GetBits(dib));

  

  int32 desiredChanels = 4;
  int32 channels = 0;
  
  //image->m_pitch = 4;
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

  image->setName(StringUtilities::toString(path.filename()));

  SPtr<Texture> texture = GraphicAPI::instance().createTexture();

  texture->initFromImage(image);

  ResoureManager::instance().m_textures.insert({ texture->getName(),texture});

  return true;
}

bool
Loader::loadTexture(const Path& path){
  return loadImage(path);
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
    auto stringName = StringUtilities::toString(newPath.filename());
    if(loadImage(newPath) || 
       manager.m_textures.find(stringName) != manager.m_textures.end()){

      gbufferFlags |= gbufferFlag;
      mat->setTexture(textureChannel, manager.m_textures[stringName]);
    }
  }
}

void 
loadTextures(SPtr<Model> model,const aiScene* loadedScene,const Path& path){

  auto& manager = ResoureManager::instance();

  for(uint32 numMaterial = 0; numMaterial < loadedScene->mNumMaterials; ++numMaterial){
    auto material = loadedScene->mMaterials[numMaterial];

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

    model->addMaterial(mat);

    mat->setName(StringUtilities::toString(MaterialName));

    manager.m_materials.insert({mat->getName(),mat});
  }
}

/*
void 
loadTextures(SPtr<Model> model)
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);
  auto& manager = ResoureManager::instance();
  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    SPtr<Mesh> oaMesh = makeSPtr<Mesh>();

    aiString f;

    String TextureName;

    Path TextureFile;

    auto material = manager.m_materials["default"];

    if(m_loadedFlags & LOADERFLAGS::kAnimation){
      material = manager.m_materials["animation"];
    }

    scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME,f);
    //TextureName = f.data-4;
    TextureName = f.C_Str();
    print(TextureName);
    TextureFile.setCompletePath(m_file.getDrive()+m_file.getDirection()+TextureName+".png");
    if(manager.loadTexture(TextureFile)){
      auto mat = copy(material);
      mat->m_diffuse = manager.m_textures[TextureFile.getCompletePath()];
      manager.m_materials.insert({TextureName,mat});
      model->m_materials.push_back(mat);

      Path texfile;

      texfile.setCompletePath(m_file.getDrive()+m_file.getDirection()+TextureName+"S.png");

      if(manager.loadTexture(texfile)){
        mat->m_specular = manager.m_textures[texfile.getCompletePath()];
      }

      texfile.setCompletePath(m_file.getDrive()+m_file.getDirection()+TextureName+"N.png");

      if(manager.loadTexture(texfile)){
        mat->m_normalMap = manager.m_textures[texfile.getCompletePath()];
      }
    }
    else{
      model->m_materials.push_back(material);
    }
    
  }
  
}
*/
/*
void 
loadSkeletons(const aiScene* loadedScene)
{
  auto& manager = ResoureManager::instance();

  auto skeleton = makeSPtr<Skeleton>();

  skeleton->m_skeleton = makeSPtr<SkeletalNode>();

  skeleton->m_globalInverse = 
    reinterpret_cast<Matrix4f*>(&loadedScene->mRootNode->mTransformation)->inverse();

  loadSkeleton(loadedScene->mRootNode,skeleton->m_skeleton,skeleton);

  manager.m_skeletons.insert({m_file.getCompletePath(),skeleton});

  skeleton->m_name = m_file.getName();
}*/
/*
void 
loadAnimations()
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);

  for(uint32 animNum = 0; animNum < scene->mNumAnimations; ++animNum){

    auto actualAnim = scene->mAnimations[animNum];
   
    auto animation = makeSPtr<Animation>();
   
    animation->m_duration = static_cast<float>(actualAnim->mDuration);
   
    animation->m_ticksPerSecond = 1.f/static_cast<float>(actualAnim->mTicksPerSecond);
   
    for(uint32 numChannel = 0; numChannel < actualAnim->mNumChannels; ++numChannel){
      
      auto actualChannel = actualAnim->mChannels[numChannel];
   
      auto node = makeSPtr<AnimNode>();
   
      node->name = actualChannel->mNodeName.C_Str();
   
      node->locations.resize(actualChannel->mNumPositionKeys);
   
      for(uint32 i = 0; i < actualChannel->mNumPositionKeys; ++i){
        Vector3f pos; 
        pos.x = actualChannel->mPositionKeys[i].mValue.x;
        pos.y = actualChannel->mPositionKeys[i].mValue.y;
        pos.z = actualChannel->mPositionKeys[i].mValue.z;
        node->locations[i] = 
        {static_cast<float>(actualChannel->mPositionKeys[i].mTime),
        pos};
      }
   
      node->scales.resize(actualChannel->mNumScalingKeys);
   
      for(uint32 i = 0; i < actualChannel->mNumScalingKeys; ++i){
        Vector3f sca; 
        sca.x = actualChannel->mScalingKeys[i].mValue.x;
        sca.y = actualChannel->mScalingKeys[i].mValue.y;
        sca.z = actualChannel->mScalingKeys[i].mValue.z;
        node->scales[i] =
        {static_cast<float>(actualChannel->mScalingKeys[i].mTime),
        sca};
      }
   
      node->rotations.resize(actualChannel->mNumRotationKeys);
   
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
   
      animation->m_nodes.insert({actualChannel->mNodeName.C_Str(),node});
      
    }
   
    ResoureManager::instancePtr()->m_animations.insert({m_file.getCompletePath(),animation});
    animation->m_name = m_file.getName();
  }

}

}*/


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
Loader::loadScene(const Path& file)
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
  
  auto model = makeSPtr<Model>();

  if(!importedScene){
    //OA_DEBUG_LOG("file "+completePath+"not found");
    //__PRETTY_FUNCTION__;
    return false;//static_cast<LOADERFLAGS::E>(m_loadedFlags);
  }
 
  if(importedScene->HasMeshes()){
    m_loadedFlags |= LOADERFLAGS::kMesh;
    loadMeshes(model,importedScene);
  }

  if(importedScene->HasMaterials()){
    m_loadedFlags |= LOADERFLAGS::kTexture;
    loadTextures(model,importedScene,file);
  }

  if(importedScene->HasAnimations()){
    m_loadedFlags |= LOADERFLAGS::kAnimation | LOADERFLAGS::kSkeleton;
  }   
  
  ResoureManager::instance().m_models.insert({StringUtilities::toString(file.c_str()),model});
  model->setName(StringUtilities::toString(file.filename()));

  return true;//static_cast<LOADERFLAGS::E>(m_loadedFlags);
}

bool
Loader::loadResource(const Path & path)
{
  auto extencion = StringUtilities::toString(path.extension());
  if(extencion == ".png" || extencion == ".jpg"){
    return loadTexture(path);
  }

  if(extencion == ".obj" || extencion == ".fbx"){
    return loadScene(path);
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
  ResoureManager::instance().m_sounds.insert({name,sound});
  return true;
}

}