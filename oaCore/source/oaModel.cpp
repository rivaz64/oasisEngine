#include "oaModel.h"
#include "oaResoureManager.h"
#include "oaSkeleton.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <stdlib.h>

using Assimp::Importer;

namespace oaEngineSDK{

void
loadSkeleton(aiNode* node,SPtr<Tree<SkeletalNode>> sNode){
  sNode->data.name = node->mName.C_Str();
  sNode->data.transform = *reinterpret_cast<Matrix4f*>(&node->mTransformation);
  sNode->childs.resize(node->mNumChildren);
  for(int i = 0; i<node->mNumChildren;++i){
    sNode->childs[i] = newSPtr<Tree<SkeletalNode>>();
    loadSkeleton(node->mChildren[i],sNode->childs[i]);
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

  if(scene->HasAnimations()){
    
    auto skeleton = newSPtr<Skeleton>();

    skeleton->skeleton = newSPtr<Tree<SkeletalNode>>();

    loadSkeleton(scene->mRootNode,skeleton->skeleton);

    ResoureManager::instancePtr()->skeletons.insert({name,skeleton});

    material = ResoureManager::instancePtr()->materials["animation"];

    animations = true;
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

    oaMesh->index.resize(static_cast<uint64>(aMesh->mNumFaces)* 3 );

    for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
    {
      aiFace* face = &aMesh->mFaces[t];
      if (face->mNumIndices != 3)
      {
        std::cout<< "Warning: Mesh face with not exactly 3 indices, ignoring this primitive."<<std::endl;
        continue;
      }

      oaMesh->index[static_cast<uint64>(t)*3] = face->mIndices[0];
      oaMesh->index[static_cast<uint64>(t)*3+1] = face->mIndices[1];
      oaMesh->index[static_cast<uint64>(t)*3+2] = face->mIndices[2];
    }

    if(!animations){
      Vector<Vertex> vertices;

      vertices.resize( aMesh->mNumVertices);
      for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
        Vertex actualVertex;
        actualVertex.location.x = aMesh->mVertices[numVertex].x;
        actualVertex.location.y = aMesh->mVertices[numVertex].y;
        actualVertex.location.z = aMesh->mVertices[numVertex].z;
        
        if(aMesh->HasTextureCoords(0)){
          actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
          actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
        }
        vertices[numVertex] = actualVertex;
      }

      oaMesh->create(vertices);
    }
    
    else{
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
          
          for(uint32 boneNum = 0; boneNum < aMesh->mNumBones; ++boneNum){
            
            auto actualBone = aMesh->mBones[boneNum];

            for(uint32 weightNum = 0; weightNum < actualBone->mNumWeights; ++weightNum){
            
              auto& actualWeight = actualBone->mWeights[weightNum];

              uint32 vertexId = actualWeight.mVertexId;

              auto& actualVertex = vertices[vertexId];

              for(uint8 i = 0; i < 4; ++i){
                if(((float*)&actualVertex.weights)[i] == 0){
                  ((uint32*)&actualVertex.ids)[i] = boneNum;
                  ((float*)&actualVertex.weights)[i] = actualWeight.mWeight;
                  break;

                }
              }
              
            }

          }

        }

      oaMesh->create(vertices);
    }
    
    meshes.push_back(oaMesh);

  }

  

  return true;
}


}

