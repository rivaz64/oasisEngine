#include "oaResoureManager.h"
#include <oaPlane.h>
#include <oaTriangle.h>
#include "oaGraphicAPI.h"
#include "oaMesh.h"
#include "oaTexture.h"
#include "oaModel.h"
#include "oaShader.h"
#include "oaMaterial.h"
#include "oaMesh.h"
#include "oaPath.h"
#include "oaShaderProgram.h"
#include "oaStaticMesh.h"
#include "oaOctree.h"
#include "oaVertexBuffer.h"


namespace oaEngineSDK{

bool 
ResoureManager::loadTexture(const Path& file)
{
/*
  if(m_textures.find(file.getCompletePath())!=m_textures.end()){
    print("texture already loaded");
    return true;
  }

  SPtr<Texture> texture = GraphicAPI::instance().createTexture();

  if(!texture->loadFromFile(file)){
    print("texture not loaded");
    return false;
  }

  m_textures[file.getCompletePath()] = texture;

  Path path(file);

  texture->m_name = path.getName();
  */
  return true;
  
}

void
ResoureManager::onStartUp()
{
  /*
  generateCircle(36);
  generateCone(36);
  generateCone(36);
  generateCilinder(36);
  generateTorus(36,36,.5f);*/
  //loadDefaulTextures();
  loadDefaultShaders();
  generateDefaultMaterials();
  //generateQuad();
  //generateTriangle();
  //generateCube();
}
/*
void 
ResoureManager::generateCircle(const uint8 n)
{
  /*meshes.insert({ "circle",makeSPtr<Mesh>() });
  Vector<Vertex> vertices;
  vertices.resize(n+1);
  vertices[0] = Vertex{ Vector3f(0.0f,0.0f, 0.0f),Vector3f(0.0f,1.0f, 0.0f), Vector2f(0.5f, 0.5f) };

  float arc = Math::TWO_PI/float(n);

  for(uint8 i = 0; i<n; ++i){
    float actualArc = arc*float(i);
    float actualCos = Math::cos(actualArc);
    float actualSin = Math::sin(actualArc);
    vertices[i+1] = Vertex{ Vector3f(actualCos,actualSin, 0.0f),Vector3f(0.0f,1.0f, 0.0f) ,Vector2f((actualCos+1.f)*.5f, (actualSin+1.f)*.5f) };
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
  /*meshes.insert({ "cone",makeSPtr<Mesh>() });
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
  /*meshes.insert({ "cilinder",makeSPtr<Mesh>() });
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
  /*meshes.insert({ "torus",makeSPtr<Mesh>() });
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
}*/

void
ResoureManager::generateQuad()
{
  auto quad = makeSPtr<StaticMesh>();

  //quad->m_vertices = {
  //  Vertex{ Vector4f(-.5f,-.5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) },
  //  Vertex{ Vector4f( .5f,-.5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f) },
  //  Vertex{ Vector4f( .5f, .5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f) },
  //  Vertex{ Vector4f(-.5f, .5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f) },
  //};
  //
  //quad->m_index = {
  //  3,1,0,
  //  2,1,3,
  //};
  //
  //quad->create();
  //
  //m_meshes.insert({ "quad",quad });
  //
  //auto modelQuad = makeSPtr<Model>();
  //
  //modelQuad->addMesh(quad);
  //
  //modelQuad->setName("quad");
  //
  //m_models.insert({ "quad",modelQuad });
  //
  //m_models["quad"]->setName("quad");
  //m_models["quad"]->addMaterial(makeSPtr<Material>());

}

void
divide(const Plane& plane, Vector<Vertex>& vertices, Vector<uint32>& index, Vector<uint32>& indexFront, Vector<uint32>& indexBack){
  
  Vector<Vertex> newPoints;
  Vector<uint32> newIndexesFront;
  Vector<uint32> newIndexesBack;
  Vector<uint32> replaceIndexes;
  Vector<uint32> finalIndexesFront;
  Vector<uint32> finalIndexesBack;
  int32 trisNum = index.size()/3;
  bool isFront;
  for(int32 i = 0; i<trisNum; ++i){
    replaceIndexes.clear();
    newIndexesFront.clear();
    newIndexesBack.clear();
    newPoints.clear();
    Triangle tri(vertices[index[i*3]],vertices[index[i*3+1]],vertices[index[i*3+2]]);
    if(tri.separate(plane,newPoints,newIndexesFront,newIndexesBack,isFront)){
      replaceIndexes.push_back(index[i*3]);
      replaceIndexes.push_back(index[i*3+1]);
      replaceIndexes.push_back(index[i*3+2]);
      replaceIndexes.push_back(vertices.size());
      vertices.push_back(newPoints[0]);
      replaceIndexes.push_back(vertices.size());
      vertices.push_back(newPoints[1]);
      //if(i==1)
      //for(int32 newIndex = 0; newIndex<3; ++newIndex){
      //  finalIndexes.push_back(replaceIndexes[newIndexes[newIndex]]);
      //}
      //else
      for(int32 newIndex : newIndexesFront){
        finalIndexesFront.push_back(replaceIndexes[newIndex]);
      }
      for(int32 newIndex : newIndexesBack){
        finalIndexesBack.push_back(replaceIndexes[newIndex]);
      }
      
    }
    else{
      if(isFront){
        finalIndexesFront.push_back(index[i*3]);
        finalIndexesFront.push_back(index[i*3+1]);
        finalIndexesFront.push_back(index[i*3+2]);
      }
      else{
        finalIndexesBack.push_back(index[i*3]);
        finalIndexesBack.push_back(index[i*3+1]);
        finalIndexesBack.push_back(index[i*3+2]);
      }
      
    }
  }
  //indexFrin = finalIndexes;
  indexFront = finalIndexesFront;
  indexBack = finalIndexesBack;
}

void 
ResoureManager::generateCube()
{
  //meshes.insert({ "cube",makeSPtr<Mesh>() });

  //Vector<SPtr<Mesh>> cubes;

  Vector<Vertex> vertices = {
    Vertex( Vector4f(-.5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f( .5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f( .5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f), Vector4f(-1.0f,0.0f, 0.0f,0.0f), Vector2f(0.0f, 0.0f)),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)),
    Vertex( Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)),
    Vertex( Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 1.0f) ),
    Vertex( Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) ),
    Vertex( Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) ),
    Vertex( Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) ),
    Vertex( Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) ),
    Vertex( Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) ),
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

  //Plane plane(Vector3f(.25,0,0),Vector3f(.25,1,0),Vector3f(.25,0,1));

  //Octree tree;
  //auto planes = tree.getPlanes();
  //Vector<uint32> indexFront;
  //Vector<uint32> indexBack;
  //Vector<Vector<uint32>> meshes;
  //meshes.push_back(index);
  //Vector<Vector<uint32>> newMeshes;
  //for(auto& plane: planes){
  //  for(Vector<uint32>& m : meshes){
  //    indexBack.clear();
  //    indexFront.clear();
  //    divide(plane, vertices,m,indexBack,indexFront);
  //    newMeshes.push_back(indexBack);
  //    newMeshes.push_back(indexFront);
  //  }
  //  meshes = newMeshes;
  //  newMeshes.clear();
  //}
  
 
  String name = "cube";//+StringUtilities::intToString(i);
  m_models.insert({name,makeSPtr<Model>()});
  auto& model = m_models[name];
  model->setName(name);
  model->addMaterial(makeSPtr<Material>());
  auto& material = model->getMaterial(0);
  material->setShader(0);
  m_materials.insert({"wall",material});
  model->addMesh(makeSPtr<Mesh>());
  auto& mesh = model->getMesh(0);
  mesh->setIndex(index);
  mesh->create(vertices.data(),sizeof(Vertex),vertices.size());
}

void ResoureManager::generateTriangle()
{
  Vector<Vector4f> vertex = {
    Vector4f(0,1,1,0),
    Vector4f(.5,0,1,0),
    Vector4f(-.5,0,1,0),
  };
  Vector<uint32> index = {0,1,2};

  Plane plane(Vector3f(.25,0,0),Vector3f(.25,1,0),Vector3f(.25,0,1));

  //Triangle tri(vertex[0].xyz,vertex[1].xyz,vertex[2].xyz);
  Vector<Vector3f> newPoints;
  Vector<uint32> newIndexes;
  
  //if(tri.separate(plane,newPoints,newIndexes)){
  //  vertex.push_back(Vector4f(newPoints[0],0));
  //  vertex.push_back(Vector4f(newPoints[1],0));
  //  index = newIndexes;
  //}

  

  //auto triangle = makeSPtr<Mesh>();
  //triangle->setIndex(index);
  //triangle->create(vertex.data(),sizeof(Vector4f),vertex.size());
  //m_models.insert({"triangle",makeSPtr<Model>()});
  //m_models["triangle"]->addMesh(triangle);
  //m_models["triangle"]->setName("triangle");
  //m_models["triangle"]->addMaterial(makeSPtr<Material>());


}

void 
createVertexShader(const String& name){
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createVertexShader();
  resourceManager.m_vertexShaders.insert({name,shader});
  shader->compileFromFile(name);
  shader->setName(name);
}

void 
createPixelShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({name,shader});
  shader->compileFromFile(name);
  shader->setName(name);
}

void 
createPixelShaders(const String& name, 
                   SPtr<Shader> vertexShader,
                   const Vector<String>& allDefines,
                   Vector<SPtr<ShaderProgram>>& shaderPrograms,
                   Vector<String>& defines, 
                   uint8 num)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  
  if(num < allDefines.size()){
    createPixelShaders(name, vertexShader, allDefines, shaderPrograms, defines, num+1);
    defines.push_back(allDefines[num]);
    createPixelShaders(name, vertexShader, allDefines, shaderPrograms, defines, num+1);
    defines.pop_back();
  }
  else{
    auto shader = graphicsApi.createPixelShader();
    shader->compileFromFile(name,defines);
    auto shaderProgram = graphicsApi.createShaderProgram();
    shaderProgram->attach(vertexShader);
    shaderProgram->attach(shader);
    shaderProgram->setChannels({"diffuse","specular","normalMap","emisive"});
    shaderPrograms.push_back(shaderProgram);

  }
}

void 
createPixelShaders(const String& name, 
                   SPtr<Shader> vertexShader,
                   const Vector<String>& allDefines,
                   Vector<SPtr<ShaderProgram>>& shaderProgram)
{
  Vector<String> defines;
  createPixelShaders(name, vertexShader, allDefines, shaderProgram,defines,0);
}

void 
createShaderProgram(const String& name, const String& vertex, const String& pixel){
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto program = graphicsApi.createShaderProgram();
  resourceManager.m_shaderPrograms.insert({name,program});
  program->attach(resourceManager.m_vertexShaders[vertex]);
  program->attach(resourceManager.m_pixelShaders[pixel]);
  program->setName(name);
}

void 
ResoureManager::loadDefaultShaders()
{
  m_vertexShaders.clear();
  m_pixelShaders.clear();
  m_shaderPrograms.clear();
  m_multiShaderPrograms.clear();
  createVertexShader("vertexShader");
  createVertexShader("animVertexShader");
  createVertexShader("vertexDebug");
  createVertexShader("screen");
  createVertexShader("position");

  createPixelShader("default");
  createPixelShader("paralax");
  createPixelShader("transparent");
  createPixelShader("debug");
  //createPixelShader("GBuffer");
  createPixelShader("lights");
  createPixelShader("ssao");
  createPixelShader("convolution");
  createPixelShader("copy");
  createPixelShader("color");
  //createPixelShader("directionalLight");
  //createPixelShader("pointLight");

  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({"directionalLight",shader});
  shader->compileFromFile("light",{"DIRECTIONAL"});
  shader->setName("directionalLight");

  shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({"pointLight",shader});
  shader->compileFromFile("light",{"POINT"});
  shader->setName("pointLight");

  createShaderProgram("default","vertexShader","default");
  createShaderProgram("animation","animVertexShader","default");
  createShaderProgram("paralax","vertexShader","paralax");
  createShaderProgram("transparent","vertexShader","transparent");
  m_shaderPrograms["transparent"]->setChannels({"diffuse","specular","normalMap"});
  createShaderProgram("debug","vertexDebug","debug");
  //createShaderProgram("GBuffer","vertexShader","GBuffer");
  //m_shaderPrograms["GBuffer"]->setChannels({"diffuse","specular","normalMap","emisive"});
  createShaderProgram("lights","screen","lights");
  createShaderProgram("color","debug","color");
  createShaderProgram("ssao","screen","ssao");
  createShaderProgram("convolution","screen","convolution");
  createShaderProgram("copy","screen","copy");
  createShaderProgram("directionalLight","screen","directionalLight");
  createShaderProgram("pointLight","screen","pointLight");

  Vector<SPtr<ShaderProgram>> gBuffer;
  createPixelShaders("GBuffer",
                     m_vertexShaders["vertexShader"],
                     {"EMISIVE","SPECULAR","NORMALS","DIFFUSE"},
                     gBuffer);
  //auto pixelShader = graphicsApi.createPixelShader();
  //resourceManager.m_pixelShaders.insert({"colorGbuffer",shader});
  //pixelShader->compileFromFile("GBuffer",{"DIFFUSE"});
  //pixelShader->setName("colorGbuffer");
  //auto program = graphicsApi.createShaderProgram(); 
  //program->attach(m_vertexShaders["vertexShader"]);
  //program->attach(pixelShader);
  //program->setChannels({"diffuse","specular","normalMap","emisive"});
  //if(gBuffer.size()==0){
  //  gBuffer.push_back(program);
  //}
  m_multiShaderPrograms.insert({"gBuffer",gBuffer});
}

void ResoureManager::loadDefaulTextures()
{
  m_textures.insert({"default",GraphicAPI::instancePtr()->createTexture()});
  Path path;
  path.setCompletePath("textures/defaultTexture.png");
  //m_textures["default"]->loadFromFile(path);
}

void 
ResoureManager::generateDefaultMaterials()
{
  //auto material = makeSPtr<Material>();
  //material->setName("debug");
  //material->setShader(m_shaderPrograms["debug"]);
  //m_materials.insert({material->getName(),material});
}

Vector<SPtr<Model>>
ResoureManager::separate(SPtr<Model> model)
{
  auto& mesh = model->getMesh(0);
  auto& indices = mesh->getIndex();
  auto vertices = mesh->getVertex();
  auto material = model->getMaterial(0);
  Octree tree;
  auto planes = tree.getPlanes();
  Vector<uint32> indexFront;
  Vector<uint32> indexBack;
  Vector<Vector<uint32>> meshes;
  meshes.push_back(indices);
  Vector<Vector<uint32>> newMeshes;
  for(auto& plane: planes){
    for(Vector<uint32>& m : meshes){
      indexBack.clear();
      indexFront.clear();
      divide(plane, vertices,m,indexBack,indexFront);
      newMeshes.push_back(indexBack);
      newMeshes.push_back(indexFront);
    }
    meshes = newMeshes;
    newMeshes.clear();
  }

  Vector<SPtr<Model>> models;
  auto  vertexB = GraphicAPI::instancePtr()->createVertexBuffer();
  vertexB->init(vertices.data(),sizeof(Vertex),vertices.size());

  for(int32 i = 0; i<8; ++i){
    String name = "cube"+StringUtilities::intToString(i);
    auto model = makeSPtr<Model>();
    model->setName(name);
    model->addMaterial(material);
    model->addMesh(makeSPtr<Mesh>());
    auto& newMesh = model->getMesh(0);
    newMesh->setIndex(meshes[i]);
    newMesh->create(vertexB);
    models.push_back(model);
  }

  return models;
  
}

}

