#include "oaResoureManager.h"
#include "oaGraphicAPI.h"
#include <iostream>

bool oaEngineSDK::ResoureManager::loadTexture(const String& file)
{
  SPtr<Texture> texture = GraphicAPI::instancePtr()->createTexture();

  if(!texture->loadFromFile(file)){
    std::cout<<"texture not loaded"<<std::endl;
    return false;
  }

  textures.insert({file,texture});

  return true;
}

void 
oaEngineSDK::ResoureManager::onStartUp()
{
  generatePlane();
  generateCube();
}

void oaEngineSDK::ResoureManager::generateCircle(const uint8 n)
{
  meshes.insert({ "circle",newSPtr<Mesh>() });
  auto& vertices =  meshes["circle"]->vertices;
  vertices.resize(n+1);
  vertices[0] = Vertex{ Vector3f(0.0f,0.0f, 0.0f), Vector2f(0.5f, 0.5f) };

  float arc = Math::TWO_PI/float(n);

  for(uint8 i = 0; i<n; ++i){
    float actualArc = arc*float(i);
    float actualCos = Math::cos(actualArc);
    float actualSin = Math::sin(actualArc);
    vertices[i+1] = Vertex{ Vector3f(actualCos,actualSin, 0.0f), Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
  }

  auto& indices =  meshes["circle"]->index;

  indices.resize(n*3);

  for(uint8 i = 0; i<n-1; ++i){
    indices[i*3]= i+1;
    indices[i*3+1]= 0;
    indices[i*3+2] = i+2;
  }

  uint8 i = n-1;
  indices[i*3]= n;
  indices[i*3+1]= 0;
  indices[i*3+2] = 1;

  meshes["circle"]->create();
}

void 
oaEngineSDK::ResoureManager::generatePlane()
{
  meshes.insert({ "plane",newSPtr<Mesh>() });
  meshes["plane"]->vertices = {
    Vertex{ Vector3f(-.5f, -.5f, 0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, 0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, 0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, 0.0f), Vector2f(0.0f, 1.0f) },
  };

  meshes["plane"]->index = {
    3,1,0,
    2,1,3,
  };

  meshes["plane"]->create();

}

void oaEngineSDK::ResoureManager::generateCube()
{
  meshes.insert({ "cube",newSPtr<Mesh>() });
  meshes["cube"]->vertices = {
    Vertex{ Vector3f(-.5f, .5f, -.5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, -.5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, .5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, .5f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, -.5f, -.5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, -.5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, .5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, -.5f, .5f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, -.5f, .5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(-.5f, -.5f, -.5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(-.5f, .5f, -.5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, .5f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(.5f, -.5f, .5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, -.5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, -.5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(.5f, .5f, .5f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, -.5f, -.5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, -.5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, -.5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, -.5f), Vector2f(0.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, -.5f, .5f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, .5f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, .5f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, .5f), Vector2f(0.0f, 1.0f) },
  };

  meshes["cube"]->index = {
    3,1,0,
    2,1,3,

    6,4,5,
    7,4,6,

    11,9,8,
    10,9,11,

    14,12,13,
    15,12,14,

    19,17,16,
    18,17,19,

    22,20,21,
    23,20,22
  };

  meshes["cube"]->create();

}
