#include "oaProceduralTerrain.h"
#include "oaVector2U.h"
void oaEngineSDK::ProceduralTerrain::init(const Grid2D<float>& data)
{
  auto size = data.getSize();
  Vector2U position;
  for(position.x=0;position.x<size.x-1;++position.x){
    for(position.y=0;position.y<size.y-1;++position.y){
      vertices.push_back(Vertex{ Vector4f(position.x+1, data.getAt(position+Vector2U(1,0)), position.y,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(1.0f, 0.0f) });
      vertices.push_back(Vertex{ Vector4f(position.x, data.getAt(position), position.y,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 0.0f) });
      vertices.push_back(Vertex{ Vector4f(position.x, data.getAt(position+Vector2U(0,1)), position.y+1,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 1.0f) });
      
      vertices.push_back(Vertex{ Vector4f(position.x+1, data.getAt(position+Vector2U(1,0)), position.y,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(1.0f, 0.0f) });
      vertices.push_back(Vertex{ Vector4f(position.x, data.getAt(position+Vector2U(0,1)), position.y+1,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 1.0f) });
      vertices.push_back(Vertex{ Vector4f(position.x+1, data.getAt(position+Vector2U(1,1)), position.y+1,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(1.0f, 1.0f) });

      uint32 isize = indices.size();
      indices.push_back(isize);
      indices.push_back(isize+1);
      indices.push_back(isize+2);
      indices.push_back(isize+3);
      indices.push_back(isize+4);
      indices.push_back(isize+5);

    } 
  }
  createNormals(vertices);
  create(vertices,indices);
}
