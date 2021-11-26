#include "oaResoureManager.h"
#include "oaGraphicAPI.h"
#include <iostream>

namespace oaEngineSDK{

bool 
ResoureManager::loadTexture(const String& file)
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
ResoureManager::onStartUp()
{
  generatePlane();
  generateCube();
  generateCircle(36);
  generateCone(36);
  generateCone(36);
  generateCilinder(36);
  loadDefaulTextures();
  loadDefaultShaders();
  generateDefaultMaterial();
}

void 
ResoureManager::generateCircle(const uint8 n)
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
ResoureManager::generateCone(const uint8 n)
{
  meshes.insert({ "cone",newSPtr<Mesh>() });
  auto& vertices =  meshes["cone"]->vertices;
  vertices.resize(n+2);
  vertices[0] = Vertex{ Vector3f(0.0f,0.0f,-.5f), Vector2f(0.5f, 0.5f) };
  vertices[1] = Vertex{ Vector3f(0.0f,0.0f, .5f), Vector2f(0.5f, 0.5f) };

  float arc = Math::TWO_PI/float(n);

  for(uint8 i = 0; i<n; ++i){
    float actualArc = arc*float(i);
    float actualCos = Math::cos(actualArc);
    float actualSin = Math::sin(actualArc);
    vertices[i+2] = Vertex{ Vector3f(actualCos,actualSin, -.5f), Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
  }

  auto& indices =  meshes["cone"]->index;

  indices.resize(n*6);

  for(uint8 i = 0; i<n-1; ++i){
    indices[i*6]= i+2;
    indices[i*6+1]= 0;
    indices[i*6+2] = i+3;

    indices[i*6+3]= i+2;
    indices[i*6+5]= 1;
    indices[i*6+4] = i+3;
  }

  uint8 i = n-1;
  indices[i*6]= n+1;
  indices[i*6+1]= 0;
  indices[i*6+2] = 2;

  indices[i*6+3]= n+1;
  indices[i*6+5]= 1;
  indices[i*6+4] = 2;

  meshes["cone"]->create();
}

void 
ResoureManager::generateCilinder(const uint8 n)
{
  meshes.insert({ "cilinder",newSPtr<Mesh>() });
  auto& vertices =  meshes["cilinder"]->vertices;
  vertices.resize((n+1)*2);
  vertices[0] = Vertex{ Vector3f(0.0f,0.0f,-.5f), Vector2f(0.5f, 0.5f) };
  vertices[1] = Vertex{ Vector3f(0.0f,0.0f, .5f), Vector2f(0.5f, 0.5f) };

  float arc = Math::TWO_PI/float(n);

  for(uint8 i = 0; i<n; ++i){
    float actualArc = arc*float(i);
    float actualCos = Math::cos(actualArc);
    float actualSin = Math::sin(actualArc);
    vertices[i*2+2] = Vertex{ Vector3f(actualCos,actualSin, -.5f), Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
    vertices[i*2+3] = Vertex{ Vector3f(actualCos,actualSin, .5f), Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
  }

   auto& indices =  meshes["cilinder"]->index;

  indices.resize(n*12);

  for(uint8 i = 0; i<n-1; ++i){
    indices[i*12]= i*2+2;
    indices[i*12+1]= 0;
    indices[i*12+2] = i*2+4;

    indices[i*12+3]= i*2+3;
    indices[i*12+5]= 1;
    indices[i*12+4] = i*2+5;

    indices[i*12+6] =  i*2+2;
    indices[i*12+7] =  i*2+4;
    indices[i*12+8] =  i*2+3;

    indices[i*12+9] =  i*2+3;
    indices[i*12+10] =  i*2+4;
    indices[i*12+11] =  i*2+5;
  }

  uint8 i = n-1;
  indices[i*12]= i*2+2;
  indices[i*12+1]= 0;
  indices[i*12+2] = 2;

  indices[i*12+3]= i*2+3;
  indices[i*12+5]= 1;
  indices[i*12+4] = 3;

  indices[i*12+6] =  i*2+2;
  indices[i*12+7] =  2;
  indices[i*12+8] =  i*2+3;

  indices[i*12+9] =  i*2+3;
  indices[i*12+10] = 2;
  indices[i*12+11] = 3;

  meshes["cilinder"]->create();
}

void 
ResoureManager::generatePlane()
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

void 
ResoureManager::generateCube()
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

void ResoureManager::loadDefaultShaders()
{
  vertexShaders.insert({"default",GraphicAPI::instancePtr()->createVertexShader()});
  pixelShaders.insert({"default",GraphicAPI::instancePtr()->createPixelShader()});

  vertexShaders["default"]->compileFromFile("shader");
  pixelShaders["default"]->compileFromFile("shader");
}

void ResoureManager::loadDefaulTextures()
{
  textures.insert({"default",GraphicAPI::instancePtr()->createTexture()});
  textures["default"]->loadFromFile("textures/download.jfif");
}

void
ResoureManager::generateDefaultMaterial()
{
  materials.insert({"default",newSPtr<Material>()});
  materials["default"]->vertexShader = vertexShaders["default"];
  materials["default"]->pixelShader = pixelShaders["default"];
  materials["default"]->textures.push_back(textures["default"]);
}

}

