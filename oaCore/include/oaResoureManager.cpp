#include "oaResoureManager.h"
#include "oaGraphicAPI.h"
#include "oaMesh.h"
#include "oaTexture.h"
#include "oaModel.h"
#include "oaShader.h"
#include "oaMaterial.h"
#include "oaMesh.h"

namespace oaEngineSDK{

bool 
ResoureManager::loadTexture(const String& file)
{
  if(textures.find(file)!=textures.end()){
    return true;
  }

  SPtr<Texture> texture = GraphicAPI::instancePtr()->createTexture();

  if(!texture->loadFromFile(file)){
    print("texture not loaded");
    return false;
  }

  textures[file] = texture;

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
  generateTorus(36,36,.5f);
  loadDefaulTextures();
  loadDefaultShaders();
  generateDefaultMaterial();
}

void 
ResoureManager::generateCircle(const uint8 n)
{
  meshes.insert({ "circle",newSPtr<Mesh>() });
  Vector<Vertex> vertices;
  vertices.resize(n+1);
  vertices[0] = Vertex{ Vector3f(0.0f,0.0f, 0.0f), Vector2f(0.5f, 0.5f) };

  float arc = Math::TWO_PI/float(n);

  for(uint8 i = 0; i<n; ++i){
    float actualArc = arc*float(i);
    float actualCos = Math::cos(actualArc);
    float actualSin = Math::sin(actualArc);
    vertices[i+1] = Vertex{ Vector3f(actualCos,actualSin, 0.0f), Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
  }

  Vector<uint32> indices;

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

  meshes["circle"]->create(vertices,indices);
}

void 
ResoureManager::generateCone(const uint8 n)
{
  meshes.insert({ "cone",newSPtr<Mesh>() });
  Vector<Vertex> vertices;
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

  Vector<uint32> indices;

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

  meshes["cone"]->create(vertices,indices);
}

void 
ResoureManager::generateCilinder(const uint8 n)
{
  meshes.insert({ "cilinder",newSPtr<Mesh>() });
  Vector<Vertex> vertices;
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

  Vector<uint32> indices;

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

  meshes["cilinder"]->create(vertices,indices);
}

void ResoureManager::generateTorus(const uint8 n, const uint8 m, const float ratio)
{
  meshes.insert({ "torus",newSPtr<Mesh>() });
  Vector<Vertex> vertices;
  vertices.resize(n*m);

  float arc1 = Math::TWO_PI/float(n);
  float arc2 = Math::TWO_PI/float(m);

  for(uint8 i = 0; i<n; ++i){
    float actualArc1 = arc1*float(i);
    float actualCos1 = Math::cos(actualArc1);
    float actualSin1 = Math::sin(actualArc1);
    for(uint8 o = 0; o<m; ++o){
      float actualArc2 = arc2*float(o);
      float actualCos2 = Math::cos(actualArc2);
      float actualSin2 = Math::sin(actualArc2);

      float r = 1.0f+ratio*actualCos2;

      vertices[i*m+o] = Vertex{ 
        Vector3f(actualCos1*r,actualSin1*r, actualSin2),
        Vector2f(0.0f,0.0f)
      };
    }
  }

  Vector<uint32> indices;

  indices.resize(n*m*6);

  uint8 i,o;

  for(i = 0; i<n-1; ++i){
    for(o = 0; o<m-1; ++o){
      indices[(i*m+o)*6] = i*m+o;
      indices[(i*m+o)*6+1] = i*m+o+1;
      indices[(i*m+o)*6+2] = (i+1)*m+o;

      indices[(i*m+o)*6+3] = i*m+o+1;
      indices[(i*m+o)*6+4] = (i+1)*m+o+1;
      indices[(i*m+o)*6+5] = (i+1)*m+o;
    }

    indices[(i*m+o)*6] = i*m+o;
    indices[(i*m+o)*6+1] = i*m;
    indices[(i*m+o)*6+2] = (i+1)*m+o;

    indices[(i*m+o)*6+3] = i*m;
    indices[(i*m+o)*6+4] = (i+1)*m;
    indices[(i*m+o)*6+5] = (i+1)*m+o;
  }

  for(o = 0; o<m-1; ++o){
    indices[(i*m+o)*6] = i*m+o;
    indices[(i*m+o)*6+1] = i*m+o+1;
    indices[(i*m+o)*6+2] = m+o;

    indices[(i*m+o)*6+3] = i*m+o+1;
    indices[(i*m+o)*6+4] = m+o+1;
    indices[(i*m+o)*6+5] = m+o;
  }

  indices[(i*m+o)*6] = i*m+o;
  indices[(i*m+o)*6+1] = i*m;
  indices[(i*m+o)*6+2] = m+o;

  indices[(i*m+o)*6+3] = i*m;
  indices[(i*m+o)*6+4] = m;
  indices[(i*m+o)*6+5] = m+o;

  meshes["torus"]->create(vertices,indices);
}

void
ResoureManager::generatePlane()
{
  meshes.insert({ "plane",newSPtr<Mesh>() });
  Vector<Vertex> vertices = {
    Vertex{ Vector3f(-.5f, -.5f, 0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector3f(.5f, -.5f, 0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector3f(.5f, .5f, 0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector3f(-.5f, .5f, 0.0f), Vector2f(0.0f, 1.0f) },
  };

  Vector<uint32> index = {
    3,1,0,
    2,1,3,
  };

  meshes["plane"]->create(vertices,index);

}

void 
ResoureManager::generateCube()
{
  meshes.insert({ "cube",newSPtr<Mesh>() });
  Vector<Vertex> vertices = {
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

  Vector<uint32> index = {
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

  meshes["cube"]->create(vertices,index);

}

void ResoureManager::loadDefaultShaders()
{
  vertexShaders.insert({"default",GraphicAPI::instancePtr()->createVertexShader()});
  vertexShaders.insert({"animation",GraphicAPI::instancePtr()->createVertexShader()});
  pixelShaders.insert({"default",GraphicAPI::instancePtr()->createPixelShader()});

  vertexShaders["default"]->compileFromFile("vertexShader");
  vertexShaders["default"]->name = "normal";

  vertexShaders["animation"]->compileFromFile("animVertexShader");
  vertexShaders["animation"]->name = "animation";

  pixelShaders["default"]->compileFromFile("shader");

}

void ResoureManager::loadDefaulTextures()
{
  textures.insert({"default",GraphicAPI::instancePtr()->createTexture()});
  textures["default"]->loadFromFile("textures/defaultTexture.png");
}

void
ResoureManager::generateDefaultMaterial()
{
  materials.insert({"default",newSPtr<Material>()});
  materials.insert({"animation",newSPtr<Material>()});

  materials["default"]->vertexShader = vertexShaders["default"];
  materials["default"]->pixelShader = pixelShaders["default"];
  materials["default"]->textures.push_back(textures["default"]);

  materials["animation"]->vertexShader = vertexShaders["animation"];
  materials["animation"]->pixelShader = pixelShaders["default"];
  materials["animation"]->textures.push_back(textures["default"]);
}

}

