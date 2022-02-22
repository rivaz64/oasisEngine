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
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image\stb_image.h>
#include "oaPath.h"
#include "oaMesh.h"
#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaMaterial.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"
#include "oaStaticMesh.h"
#include "oaSkeletalMesh.h"
#include "oaLogger.h"
#include "oaImage.h"
#include "oaTexture.h"
#include "oaGraphicAPI.h"


using Assimp::Importer;

namespace oaEngineSDK {

void
loadSkeleton(aiNode* node,SPtr<SkeletalNode> sNode,SPtr<Skeleton> skeleton)
{

  sNode->name = node->mName.C_Str();
  
  print(node->mName.C_Str());

  sNode->transform = reinterpret_cast<Matrix4f*>(&node->mTransformation)->transposed();

  skeleton->m_boneMaping.insert({sNode->name,sNode->transform});

  sNode->childs.resize(node->mNumChildren);
  for(uint32 i = 0; i < node->mNumChildren; ++i){
    sNode->childs[i] = newSPtr<SkeletalNode>();
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}



void
readIndexes(SPtr<Mesh> mesh, aiMesh* aMesh){
  
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
}

void
readStaticMesh(SPtr<StaticMesh> mesh, aiMesh* aMesh){
  
  mesh->setVertexNum(static_cast<SIZE_T>(aMesh->mNumVertices));

  for(SIZE_T numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){

    auto& actualVertex = mesh->getVertexAt(numVertex);

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
      actualVertex.textureCord.y = aMesh->mTextureCoords[0][numVertex].y;
    }
  }
}

void
readSkeletalMesh(SPtr<SkeletalMesh> mesh, aiMesh* aMesh){

  auto& bones = mesh->m_bones;

  auto& vertices = mesh->m_vertices;

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

      SIZE_T boneIndex;

      if(mesh->m_boneMaping.find(boneName) == mesh->m_boneMaping.end()){
        boneIndex = bonesNum;
        mesh->m_boneMaping.insert({boneName,bonesNum});
        bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
        //boneNames.push_back(boneName);
        ++bonesNum;
      }
      else{

        boneIndex = mesh->m_boneMaping[boneName];
      }

      //boneIndex = skeleton->boneMaping[boneName];

      actualBone = aMesh->mBones[boneIndex];

      for(SIZE_T weightNum = 0; weightNum < actualBone->mNumWeights; ++weightNum){
      
        auto& actualWeight = actualBone->mWeights[weightNum];

        SIZE_T vertexId = actualWeight.mVertexId;

        auto& actualVertex = vertices[vertexId];

        for(uint8 i = 0; i < 8; ++i){
          if(((float*)&actualVertex.weights)[i] == 0){
            ((uint32*)&actualVertex.ids)[i] = boneIndex;
            ((float*)&actualVertex.weights)[i] = actualWeight.mWeight;
            break;

          }
        } 
      }
    }
  }
}

void 
loadMeshes(SPtr<Model> model,const aiScene* loadedScene)
{
  for(uint32 numMesh = 0; numMesh < loadedScene->mNumMeshes; ++numMesh){

    auto& aMesh = loadedScene->mMeshes[numMesh];

    auto mesh = newSPtr<StaticMesh>();

    readStaticMesh(cast<StaticMesh>(mesh),aMesh);

    model->addMaterial(ResoureManager::instance().m_materials["default"]);

    /*if(aMesh->HasBones()){

    }
    else{
      readSkeletalMesh(cast<SkeletalMesh>(mesh),aMesh);
      
    }*/

    readIndexes(mesh,aMesh);
    
    mesh->create();
    model->addMesh(mesh);
  }
}

bool
loadImage(const Path& path){
  String s = StringUtilities::toString(path.getCompletePath());
  FIBITMAP* dib(0);
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

  auto file = s.c_str();
  fif = FreeImage_GetFileType(file,0);

  if (fif == FIF_UNKNOWN){
    
    fif = FreeImage_GetFIFFromFilename(file);
  }

  if (fif == FIF_UNKNOWN){
    //OA_WARNING_LOG("unknown format of image"+file);
    return false;
  }
    
  if (FreeImage_FIFSupportsReading(fif)) {
    dib = FreeImage_Load(fif, file);
    if (!dib){
      //OA_WARNING_LOG("file "+path.getCompletePath() + " could not be loaded");
      return false;
    }
    dib = FreeImage_ConvertTo32Bits(dib);
  }

  
   auto image = newSPtr<Image>();
  image->m_pixels = FreeImage_GetBits(dib);
  image->m_width = FreeImage_GetWidth(dib);
  image->m_height = FreeImage_GetHeight(dib);
  image->m_pitch = FreeImage_GetPitch(dib);

 

  /*int32 desiredChanels = 4;
  int32 channels = 0;

  image->m_pixels = stbi_load(s.c_str(),
                           &image->m_width,
                           &image->m_height,
                           &channels,
                           desiredChanels);*/

  if (image->m_pixels == 0 || image->m_width == 0 || image->m_height == 0){
    //OA_WARNING_LOG(path.getCompletePath() + " is an invalid image");
    return false;
  }

  SPtr<Texture> texture = GraphicAPI::instance().createTexture();

  texture->init(image->m_width,image->m_height);

  texture->initFromImage(image);

  ResoureManager::instance().m_textures.insert({ StringUtilities::toString(path.getName()),texture});

  texture->m_name =  StringUtilities::toString(path.getName());

  return true;
}

bool
Loader::loadTexture(const Path& path){
  return loadImage(path);
}

void 
loadTextures(SPtr<Model> model,const aiScene* loadedScene,const Path& path){

  auto& manager = ResoureManager::instance();

  for(uint32 numMaterial = 0; numMaterial < loadedScene->mNumMaterials; ++numMaterial){
    auto material = loadedScene->mMaterials[numMaterial];

    aiString notMyString;

    material->Get(AI_MATKEY_NAME,notMyString);

    WString MaterialName = StringUtilities::toWString(notMyString.C_Str());

    auto mat = copy(model->getMaterial(numMaterial));

    Path texturePath;

    WString textureName = MaterialName;

    texturePath.setCompletePath(path.getDrive()+path.getDirection()+textureName+L".png");

    if(loadImage(texturePath)){
      mat->m_diffuse = manager.m_textures[ StringUtilities::toString(textureName)];
    }

    textureName = MaterialName+L"N";

    texturePath.setCompletePath(path.getDrive()+path.getDirection()+textureName+L".png");

    if(loadImage(texturePath)){
      mat->m_normalMap = manager.m_textures[ StringUtilities::toString(textureName)];
    }

    textureName = MaterialName+L"S";

    texturePath.setCompletePath(path.getDrive()+path.getDirection()+textureName+L".png");

    if(loadImage(texturePath)){
      mat->m_specular = manager.m_textures[ StringUtilities::toString(textureName)];
    }

    model->setMaterial(mat,numMaterial);
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
    SPtr<Mesh> oaMesh = newSPtr<Mesh>();

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

  auto skeleton = newSPtr<Skeleton>();

  skeleton->m_skeleton = newSPtr<SkeletalNode>();

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
   
    auto animation = newSPtr<Animation>();
   
    animation->m_duration = static_cast<float>(actualAnim->mDuration);
   
    animation->m_ticksPerSecond = 1.f/static_cast<float>(actualAnim->mTicksPerSecond);
   
    for(uint32 numChannel = 0; numChannel < actualAnim->mNumChannels; ++numChannel){
      
      auto actualChannel = actualAnim->mChannels[numChannel];
   
      auto node = newSPtr<AnimNode>();
   
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
Loader::load(LOADERFLAGS::E flags)
{
/*
  auto model = newSPtr<Model>();
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

LOADERFLAGS::E
Loader::checkForLoad(const Path& file)
{
  auto flags = aiProcess_Triangulate | 
               aiProcess_GenSmoothNormals | 
               aiProcess_OptimizeMeshes | 
               aiProcess_OptimizeGraph |
               aiProcess_CalcTangentSpace;
  Importer importer;

  String completePath = StringUtilities::toString(file.getCompletePath());

  const aiScene* importedScene = importer.ReadFile(completePath.c_str(),flags);
  
  auto model = newSPtr<Model>();

  if(!importedScene){
    //OA_DEBUG_LOG("file "+completePath+"not found");
    //__PRETTY_FUNCTION__;
    return static_cast<LOADERFLAGS::E>(m_loadedFlags);
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

   
  
  ResoureManager::instance().m_models.insert({StringUtilities::toString(file.getCompletePath()),model});
  model->m_name =StringUtilities::toString(file.getName());

  return static_cast<LOADERFLAGS::E>(m_loadedFlags);
}

}