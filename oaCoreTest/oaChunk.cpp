#include "oaChunk.h"



namespace oaEngineSDK{

Vector<Vector<Vertex>> quads = {
  {
    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 1.0f) },
    Vertex{ Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f) },
  },
  {
    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f), Vector4f(-1.0f,0.0f, 0.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f) },
  },
  {
    Vertex{ Vector4f(-.5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f, .5f,  .5f ,0.0f), Vector4f(0.0f,1.0f,  0.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 1.0f) },
  },
  {
    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f) },

  },
  {
    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  1.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  1.0f,0.0f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  1.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  1.0f,0.0f), Vector2f(1.0f, 0.0f) },

  },
  {
    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 1.0f) },
  }
};

void 
Chunk::init(const Grid3D<float>& data)
{
  Vector3U position;
  Vector3U size = data.getSize();
  for(position.x = 0; position.x<size.x;++position.x){
    for(position.y = 0; position.y<size.y;++position.y){
      for(position.z = 0; position.z<size.z;++position.z){
        if(hasCube(position,data)){
          createCubeAt(position,data);
        }
      }
    }
  }
  create(vertices,indices);
}

void 
Chunk::createCubeAt(const Vector3U& position,const Grid3D<float>& data)
{
  uint8 i = 0;
  for(auto direction: Vector3I::DIRECTIONS){
    uint32 actual = vertices.size();
    auto newVec = Vector3I(position.x,position.y,position.z)+*direction;
    if(!data.isIn(newVec)){
      for(auto quad: quads[i]){
        auto vertex = quad;
        vertex.location.x += position.x + .5f;
        vertex.location.y += position.y + .5f;
        vertex.location.z += position.z + .5f;
        vertices.push_back(vertex);
      }
      indices.push_back(actual+3);
      indices.push_back(actual+1);
      indices.push_back(actual  );
      indices.push_back(actual+2);
      indices.push_back(actual+1);
      indices.push_back(actual+3);
    }
    else if(!hasCube(Vector3U(newVec.x,newVec.y,newVec.z),data)){
      for(auto quad: quads[i]){
        auto vertex = quad;
        vertex.location.x += position.x + .5f;
        vertex.location.y += position.y + .5f;
        vertex.location.z += position.z + .5f;
        vertices.push_back(vertex);
      }
      indices.push_back(actual+3);
      indices.push_back(actual+1);
      indices.push_back(actual  );
      indices.push_back(actual+2);
      indices.push_back(actual+1);
      indices.push_back(actual+3);
      
    }
    

    ++i;
  }
}

bool 
Chunk::hasCube(const Vector3U& position, const Grid3D<float>& data)
{
  return data.getAt(position) >0.0f;
}

}

