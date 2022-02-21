#include "oaSerializer.h"
#include "oaModel.h"
#include "oaPath.h"
#include "oaMesh.h"
#include "oaStaticMesh.h"

namespace oaEngineSDK{



void
Serializer::init(const Path& path)
{
  file.open(StringUtilities::toString(path.getCompletePath()),std::fstream::out|std::fstream::in);
}

void
Serializer::encodeModel(SPtr<Model> model)
{
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
  }
}

SPtr<Model> 
Serializer::decodeModel()
{
  /*auto model = newSPtr<Model>();

  SIZE_T meshNum;

  file.read(reinterpret_cast<char*>(&meshNum),sizeof(SIZE_T));

  model->setNumOfMeshes(meshNum);

  SIZE_T indexNum;

  for(SIZE_T meshN = 0; meshN < meshNum; meshN++){
    auto& mesh = model->getMesh(meshN);

    file.read(reinterpret_cast<char*>(&indexNum),sizeof(SIZE_T));

    mesh->setIndexNum(indexNum);

    auto indexData = mesh->getIndex().data();

    istringstream is;

    istream_iterator<uint32>(is);

    file.read(reinterpret_cast<char*>(indexData),sizeof(uint32)*indexNum);

    auto staticMesh = cast<StaticMesh>(mesh);

    SIZE_T vertexNum = staticMesh->getVertexNum();

    file.write(reinterpret_cast<char*>(&vertexNum),sizeof(SIZE_T));

    auto vertexData = staticMesh->getVertex().data();

    file.write(reinterpret_cast<const char*>(vertexData),sizeof(Vertex)*vertexNum);
  }
  */
  return SPtr<Model>();
}

}

