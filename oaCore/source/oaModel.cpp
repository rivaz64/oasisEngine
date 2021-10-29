#include "oaModel.h"
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
    uint32 vertindexoffset = 0;
    for(uint32 numVertex = 0; numVertex < aMesh->mNumVertices; ++numVertex){
      Vertex actualVertex;
      actualVertex.location.x = aMesh->mVertices[numVertex].x;
      actualVertex.location.y = aMesh->mVertices[numVertex].y;
      actualVertex.location.z = aMesh->mVertices[numVertex].z;
      oaMesh->vertices.push_back(actualVertex);
    }

    for (uint32 t = 0; t < aMesh->mNumFaces; ++t)
    {
      aiFace* face = &aMesh->mFaces[t];
      if (face->mNumIndices != 3)
      {
        std::cout<< "Warning: Mesh face with not exactly 3 indices, ignoring this primitive."<<std::endl;
        continue;
      }

      oaMesh->index.push_back(face->mIndices[0]);
      oaMesh->index.push_back(face->mIndices[1]);
      oaMesh->index.push_back(face->mIndices[2]);
    }

    oaMesh->create();

    meshes.push_back(oaMesh);

  }

  

  return true;
}

}

