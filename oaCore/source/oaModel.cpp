/**
* @file oaModel.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"
#include "oaMesh.h"
#include "oaMaterial.h"
#include "oaPath.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <stdlib.h>

using Assimp::Importer;

namespace oaEngineSDK{

void
loadSkeleton(aiNode* node,SPtr<SkeletalNode> sNode,SPtr<Skeleton> skeleton){

  sNode->name = node->mName.C_Str();
  
  sNode->transform = reinterpret_cast<Matrix4f*>(&node->mTransformation)->transposed();

  skeleton->boneMaping.insert({sNode->name,sNode->transform});

  sNode->childs.resize(node->mNumChildren);
  for(int i = 0; i<node->mNumChildren;++i){
    sNode->childs[i] = newSPtr<SkeletalNode>();
    loadSkeleton(node->mChildren[i],sNode->childs[i],skeleton);
  }
}

bool 
Model::loadFromFile(const Path& file)
{

  Importer importer;

  auto flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph;

  const aiScene* scene = importer.ReadFile(file.getCompletePath(),flags);
  
  if(!scene){
    print("model not found");
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

        animation->nodes.insert({actualChannel->mNodeName.C_Str(),node});
        
      }

      ResoureManager::instancePtr()->animations.insert({name,animation});

    }

  }

  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    SPtr<Mesh> oaMesh = newSPtr<Mesh>();

    aiString f;

    String TextureName;

    Path TextureFile;

    scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME,f);
    TextureName = f.C_Str();
    TextureFile.setCompletePath("textures/"+TextureName+".png");
    if(ResoureManager::instancePtr()->loadTexture(TextureFile)){
      auto mat = copy(material);
      mat->textures[0] = ResoureManager::instancePtr()->textures[TextureFile.getCompletePath()];
      ResoureManager::instancePtr()->materials.insert({TextureName,mat});
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
        print("Warning: Mesh face with not exactly 3 indices, ignoring this primitive."); 

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

        actualVertex.location.x = aMesh->mVertices[numVertex].x;
        actualVertex.location.y = aMesh->mVertices[numVertex].y;
        actualVertex.location.z = aMesh->mVertices[numVertex].z;
        actualVertex.location.w = 1.0f;

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

        actualVertex.location.w = 7;
        
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

            if(oaMesh->boneMaping.find(boneName) == oaMesh->boneMaping.end()){
              boneIndex = bonesNum;
              oaMesh->boneMaping.insert({boneName,bonesNum});
              bones.push_back(*reinterpret_cast<Matrix4f*>(&actualBone->mOffsetMatrix));
              //boneNames.push_back(boneName);
              ++bonesNum;
            }
            else{
              boneIndex = oaMesh->boneMaping[boneName];
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
    
    meshes.push_back(oaMesh);

  }

  return true;
}


}

