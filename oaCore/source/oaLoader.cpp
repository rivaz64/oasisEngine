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
#include "oaPath.h"
#include "oaMesh.h"
#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaMaterial.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"


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
  for(int i = 0; i<node->mNumChildren;++i){
    sNode->childs[i] = newSPtr<SkeletalNode>();
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}

Loader::Loader()
{
  m_importer = new Importer;
}

Loader::~Loader()
{
  delete m_importer;
}

LOADERFLAGS::E
Loader::checkForLoad(const Path& _file)
{
  m_file = _file;

  auto flags = aiProcess_Triangulate | 
               aiProcess_GenSmoothNormals | 
               aiProcess_OptimizeMeshes | 
               aiProcess_OptimizeGraph;

  m_sceneI = static_cast<Importer*>(m_importer)->ReadFile(m_file.getCompletePath(),flags);
  
  if(!m_sceneI){
    print("file not found");
    return static_cast<LOADERFLAGS::E>(m_loadedFlags);
  }
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);
  if(scene->HasMeshes()){
    m_loadedFlags |= LOADERFLAGS::MESH;

  }

  if(scene->HasMaterials()){
    m_loadedFlags |= LOADERFLAGS::TEXTURE;
  }

  if(scene->HasAnimations()){
    m_loadedFlags |= LOADERFLAGS::ANIMATION | LOADERFLAGS::SKELETON;
  }

  return static_cast<LOADERFLAGS::E>(m_loadedFlags);
}

void
Loader::load(LOADERFLAGS::E flags)
{
  auto model = newSPtr<Model>();
  if(flags & LOADERFLAGS::MESH){
    loadMeshes(model);
  }
  if(flags & LOADERFLAGS::TEXTURE){
    loadTextures(model);
  }
  if(flags & LOADERFLAGS::SKELETON){
    loadSkeletons(model);
  }
  if(flags & LOADERFLAGS::ANIMATION){
    loadAnimations(model);
  }
  ResoureManager::instance().models.insert({m_file.getCompletePath(),model});
  model->m_name = m_file.getName();
}

void Loader::loadMeshes(SPtr<Model> model)
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);
  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    SPtr<Mesh> oaMesh = newSPtr<Mesh>();

    Vector<uint32> index;

    index.resize(static_cast<uint64>(aMesh->mNumFaces)* 3 );

    for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
    {
      aiFace* face = &aMesh->mFaces[t];
      if (face->mNumIndices != 3)
      {
        print("Warning: Mesh face with not exactly 3 indices, ignoring this primitive."); 

        continue;
      }

      index[static_cast<uint64>(t)*3] = face->mIndices[0];
      index[static_cast<uint64>(t)*3+1] = face->mIndices[1];
      index[static_cast<uint64>(t)*3+2] = face->mIndices[2];
    }

    if(!(m_loadedFlags & LOADERFLAGS::ANIMATION)){
      Vector<Vertex> vertices;

      vertices.resize( aMesh->mNumVertices);
      for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
        Vertex actualVertex;

        actualVertex.location.x = aMesh->mVertices[numVertex].x*m_importScale;
        actualVertex.location.y = aMesh->mVertices[numVertex].y*m_importScale;
        actualVertex.location.z = aMesh->mVertices[numVertex].z*m_importScale;
        actualVertex.normal.x = aMesh->mNormals[numVertex].x;
        actualVertex.normal.y = aMesh->mNormals[numVertex].y;
        actualVertex.normal.z = aMesh->mNormals[numVertex].z;

        if(aMesh->HasTextureCoords(0)){
          actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
          actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
        }
        vertices[numVertex] = actualVertex;
      }
      oaMesh->create(vertices,index);
      //oaMesh->create<Vertex>(vertices,index);
    }
    else{
      
      Vector<Matrix4f> bones;

      //Vector<String> boneNames;

      Vector<AnimationVertex> vertices;

      vertices.resize( aMesh->mNumVertices);
      for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
        AnimationVertex actualVertex;
        actualVertex.location.x = aMesh->mVertices[numVertex].x;
        actualVertex.location.y = aMesh->mVertices[numVertex].y;
        actualVertex.location.z = aMesh->mVertices[numVertex].z;

        
        
        if(aMesh->HasTextureCoords(0)){
          actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
          actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
        }

        vertices[numVertex] = actualVertex;
      }

      if(aMesh->HasBones()){
          
          //Map<String,uint32> boneMaping;

        uint32 bonesNum=0;

        for(uint32 boneNum = 0; boneNum < aMesh->mNumBones; ++boneNum){

          auto actualBone = aMesh->mBones[boneNum];

          String boneName = actualBone->mName.C_Str();

          uint32 boneIndex;

          if(oaMesh->m_boneMaping.find(boneName) == oaMesh->m_boneMaping.end()){
            boneIndex = bonesNum;
            oaMesh->m_boneMaping.insert({boneName,bonesNum});
            bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
            //boneNames.push_back(boneName);
            ++bonesNum;
          }
          else{

            boneIndex = oaMesh->m_boneMaping[boneName];
          }

          //boneIndex = skeleton->boneMaping[boneName];

          actualBone = aMesh->mBones[boneIndex];

          for(uint32 weightNum = 0; weightNum < actualBone->mNumWeights; ++weightNum){
          
            auto& actualWeight = actualBone->mWeights[weightNum];

            uint32 vertexId = actualWeight.mVertexId;

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
      
      oaMesh->create(vertices,index,bones);
    }
    
   model->m_meshes.push_back(oaMesh);
  }
}

void Loader::loadTextures(SPtr<Model> model)
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);
  auto& manager = ResoureManager::instance();
  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    SPtr<Mesh> oaMesh = newSPtr<Mesh>();

    aiString f;

    String TextureName;

    Path TextureFile;

    auto material = manager.materials["default"];

    if(m_loadedFlags & LOADERFLAGS::ANIMATION){
      material = manager.materials["animation"];
    }

    scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME,f);
    TextureName = f.C_Str();

    TextureFile.setCompletePath(m_file.getDrive()+m_file.getDirection()+TextureName+".png");
    if(manager.loadTexture(TextureFile)){
      auto mat = copy(material);
      mat->m_textures[0] = manager.textures[TextureFile.getCompletePath()];
      manager.materials.insert({TextureName,mat});
      model->m_materials.push_back(mat);
    }
    else{
      model->m_materials.push_back(material);
    }
    
  }
  
}

void 
Loader::loadSkeletons(SPtr<Model> model)
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);

  auto& manager = ResoureManager::instance();

  auto skeleton = newSPtr<Skeleton>();

  skeleton->m_skeleton = newSPtr<SkeletalNode>();

  skeleton->m_globalInverse = 
    reinterpret_cast<Matrix4f*>(&scene->mRootNode->mTransformation)->inverse();

  loadSkeleton(scene->mRootNode,skeleton->m_skeleton,skeleton);

  manager.skeletons.insert({m_file.getCompletePath(),skeleton});

  skeleton->m_name = m_file.getName();
}

void Loader::loadAnimations(SPtr<Model> model)
{
  const aiScene* scene = static_cast<const aiScene*>(m_sceneI);

  auto& manager = ResoureManager::instance();

  for(uint32 animNum = 0; animNum < scene->mNumAnimations; ++animNum){

    auto actualAnim = scene->mAnimations[animNum];
   
    auto animation = newSPtr<Animation>();
   
    animation->m_duration = actualAnim->mDuration;
   
    animation->m_ticksPerSecond = 1.f/actualAnim->mTicksPerSecond;
   
    for(uint32 numChannel = 0; numChannel < actualAnim->mNumChannels; ++numChannel){
      
      auto actualChannel = actualAnim->mChannels[numChannel];
   
      auto node = newSPtr<AnimNode>();
   
      node->name = actualChannel->mNodeName.C_Str();
   
      node->locations.resize(actualChannel->mNumPositionKeys);
   
      for(int i = 0; i < actualChannel->mNumPositionKeys; ++i){
        Vector3f pos; 
        pos.x = actualChannel->mPositionKeys[i].mValue.x;
        pos.y = actualChannel->mPositionKeys[i].mValue.y;
        pos.z = actualChannel->mPositionKeys[i].mValue.z;
        node->locations[i] = 
        {actualChannel->mPositionKeys[i].mTime,
        pos};
      }
   
      node->scales.resize(actualChannel->mNumScalingKeys);
   
      for(int i = 0; i < actualChannel->mNumScalingKeys; ++i){
        Vector3f sca; 
        sca.x = actualChannel->mScalingKeys[i].mValue.x;
        sca.y = actualChannel->mScalingKeys[i].mValue.y;
        sca.z = actualChannel->mScalingKeys[i].mValue.z;
        node->scales[i] =
        {actualChannel->mScalingKeys[i].mTime,
        sca};
      }
   
      node->rotations.resize(actualChannel->mNumRotationKeys);
   
      for(int i = 0; i < actualChannel->mNumRotationKeys; ++i){
        Quaternion q;
   
        q.i = actualChannel->mRotationKeys[i].mValue.x;
        q.j = actualChannel->mRotationKeys[i].mValue.y;
        q.k = actualChannel->mRotationKeys[i].mValue.z;
        q.r = actualChannel->mRotationKeys[i].mValue.w;
   
        auto asMat = actualChannel->mRotationKeys[i].mValue.GetMatrix();
   
        auto oaMat = q.toMatrix();
   
        node->rotations[i] = 
        {actualChannel->mRotationKeys[i].mTime,q};
      }
   
      animation->m_nodes.insert({actualChannel->mNodeName.C_Str(),node});
      
    }
   
    ResoureManager::instancePtr()->animations.insert({m_file.getCompletePath(),animation});
    animation->m_name = m_file.getName();
  }

}

}



