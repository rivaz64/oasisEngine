#include "oaModel.h"
#include "oaResoureManager.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <iostream>

using Assimp::Importer;

namespace oaEngineSDK{

bool Model::loadFromFile(String file)
{
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

  for(uint32 numMesh = 0; numMesh < scene->mNumMeshes; ++numMesh){
    auto aMesh = scene->mMeshes[numMesh];
    auto oaMesh = newSPtr<Mesh>();

    aiString f;
    scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME,f);
    String file = f.C_Str();
    file = "textures/"+file+".png";
    if(ResoureManager::instancePtr()->loadTexture(file)){
      textures.push_back(ResoureManager::instancePtr()->textures[file]);
    }
    else{
      break;
    }

    uint32 vertindexoffset = 0;
    oaMesh->vertices.resize( aMesh->mNumVertices);
    for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
      Vertex actualVertex;
      actualVertex.location.x = aMesh->mVertices[numVertex].x;
      actualVertex.location.y = aMesh->mVertices[numVertex].y;
      actualVertex.location.z = aMesh->mVertices[numVertex].z;
      
      if(aMesh->HasTextureCoords(0)){
        actualVertex.textureCord.x = aMesh->mTextureCoords[0][numVertex].x;
        actualVertex.textureCord.y = 1.f-aMesh->mTextureCoords[0][numVertex].y;
      }
      oaMesh->vertices[numVertex] = actualVertex;
    }

    oaMesh->index.resize(aMesh->mNumFaces * 3);

    for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
    {
      aiFace* face = &aMesh->mFaces[t];
      if (face->mNumIndices != 3)
      {
        std::cout<< "Warning: Mesh face with not exactly 3 indices, ignoring this primitive."<<std::endl;
        continue;
      }

      oaMesh->index[t*3] = face->mIndices[0];
      oaMesh->index[t*3+1] = face->mIndices[1];
      oaMesh->index[t*3+2] = face->mIndices[2];
    }

    oaMesh->create();
    
    
    meshes.push_back(oaMesh);

  }

  

  return true;
}

}

