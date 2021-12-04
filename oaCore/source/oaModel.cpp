/**
* @file oaModel.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <stdlib.h>

using Assimp::Importer;

namespace oaEngineSDK{

void
loadSkeleton(aiNode* node,SPtr<SkeletalNode> sNode,SPtr<Skeleton> skeleton){

  sNode->name = node->mName.C_Str();
  
  sNode->transform = *reinterpret_cast<Matrix4f*>(&node->mTransformation);

  skeleton->boneMaping.insert({sNode->name,Matrix4f::IDENTITY});

  sNode->childs.resize(node->mNumChildren);
  for(int i = 0; i<node->mNumChildren;++i){
    sNode->childs[i] = newSPtr<SkeletalNode>();
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}

bool 
Model::loadFromFile(String file)
{
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char ext[_MAX_EXT];
  char name[_MAX_FNAME];
  _splitpath(file.c_str(), drive,dir,name , ext);

  Importer importer;
  const aiScene* scene = importer.ReadFile(file, aiProcess_GenSmoothNormals |
                                           aiProcess_CalcTangentSpace |
                                           aiProcess_Triangulate |
                                           aiProcess_JoinIdenticalVertices |
                                           aiProcess_SortByPType);
  
  if(!scene){
    std::cout<<"model not found"<<std::endl;
    return false;
  }

  meshes.clear();

  SPtr<Material> material = ResoureManager::instancePtr()->materials["default"];

  bool animations = false;

  SPtr<Skeleton> skeleton;

  if(scene->HasAnimations()){
    
    skeleton = newSPtr<Skeleton>();

    skeleton->skeleton = newSPtr<SkeletalNode>();

    skeleton->globalInverse = 
      reinterpret_cast<Matrix4f*>(&scene->mRootNode->mTransformation)->inverse();

    loadSkeleton(scene->mRootNode,skeleton->skeleton,skeleton);

    ResoureManager::instancePtr()->skeletons.insert({name,skeleton});

    material = ResoureManager::instancePtr()->materials["animation"];

    animations = true;

    for(uint32 animNum = 0; animNum < scene->mNumAnimations; ++animNum){

      auto actualAnim = scene->mAnimations[animNum];

      auto animation = newSPtr<Animation>();

      animation->duration = actualAnim->mDuration;

      animation->ticksPerSecond = 1.f/actualAnim->mTicksPerSecond;

      for(uint32 numChannel = 0; numChannel < actualAnim->mNumChannels; ++numChannel){
        
        auto actualChannel = actualAnim->mChannels[numChannel];

        auto node = newSPtr<AnimNode>();

        node->name = actualChannel->mNodeName.C_Str();

        node->locations.resize(actualChannel->mNumPositionKeys);

        for(int i = 0; i < actualChannel->mNumPositionKeys; ++i){
          
          node->locations[i] = 
          {actualChannel->mPositionKeys[i].mTime,
          *reinterpret_cast<Vector3f*>(&actualChannel->mPositionKeys[i].mValue)};
        }

        node->scales.resize(actualChannel->mNumScalingKeys);

        for(int i = 0; i < actualChannel->mNumScalingKeys; ++i){
          node->scales[i] =
          {actualChannel->mScalingKeys[i].mTime,
          *reinterpret_cast<Vector3f*>(&actualChannel->mScalingKeys[i].mValue)};
        }

        node->rotations.resize(actualChannel->mNumRotationKeys);

        for(int i = 0; i < actualChannel->mNumRotationKeys; ++i){
          node->rotations[i] = 
          {actualChannel->mRotationKeys[i].mTime,
          (*reinterpret_cast<Quaternion*>(&actualChannel->mRotationKeys[i])).normal()};
        }

        animation->nodes.insert({actualChannel->mNodeName.C_Str(),node});
        
      }

      ResoureManager::instancePtr()->animations.insert({name,animation});

    }

  }

  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    auto oaMesh = newSPtr<Mesh>();

    aiString f;
    scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME,f);
    file = f.C_Str();
    file = "textures/"+file+".png";
    if(ResoureManager::instancePtr()->loadTexture(file)){
      auto mat = copy(material);
      mat->textures[0] = ResoureManager::instancePtr()->textures[file];
      materials.push_back(mat);
    }
    else{
      materials.push_back(material);
    }

    Vector<uint32> index;

    index.resize(static_cast<uint64>(aMesh->mNumFaces)* 3 );

    for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
    {
      aiFace* face = &aMesh->mFaces[t];
      if (face->mNumIndices != 3)
      {
        std::cout<< 
        "Warning: Mesh face with not exactly 3 indices, ignoring this primitive."
        <<std::endl;

        continue;
      }

      index[static_cast<uint64>(t)*3] = face->mIndices[0];
      index[static_cast<uint64>(t)*3+1] = face->mIndices[1];
      index[static_cast<uint64>(t)*3+2] = face->mIndices[2];
    }

    if(!animations){
      Vector<Vertex> vertices;

      vertices.resize( aMesh->mNumVertices);
      for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
        Vertex actualVertex;

        actualVertex.location = *reinterpret_cast<Vector3f*>(&aMesh->mVertices[numVertex]);
        
        if(aMesh->HasTextureCoords(0)){
          actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
          actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
        }
        vertices[numVertex] = actualVertex;
      }

      oaMesh->create(vertices,index);
    }
    
    else{
      
      Vector<Matrix4f> bones;

      Vector<String> boneNames;

      Vector<AnimationVertex> vertices;

      vertices.resize( aMesh->mNumVertices);
      for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
        AnimationVertex actualVertex;
        actualVertex.location.x = aMesh->mVertices[numVertex].x;
        actualVertex.location.y = aMesh->mVertices[numVertex].y;
        actualVertex.location.z = aMesh->mVertices[numVertex].z;

        actualVertex.location.w = 7;
        
        if(aMesh->HasTextureCoords(0)){
          actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
          actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
        }

        vertices[numVertex] = actualVertex;
      }

      if(aMesh->HasBones()){
          
          Map<String,uint32> boneMaping;

          uint32 bonesNum=0;

          for(uint32 boneNum = 0; boneNum < aMesh->mNumBones; ++boneNum){

            auto actualBone = aMesh->mBones[boneNum];

            String boneName = actualBone->mName.C_Str();

            uint32 boneIndex;

            if(boneMaping.find(boneName) == boneMaping.end()){
              boneIndex = bonesNum;
              boneMaping.insert({boneName,bonesNum});
              bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
              boneNames.push_back(boneName);
              ++bonesNum;
            }
            else{
              boneIndex = boneMaping[boneName];
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

      oaMesh->create(vertices,index,bones,boneNames);
    }
    
    meshes.push_back(oaMesh);

  }

  return true;
}


}

