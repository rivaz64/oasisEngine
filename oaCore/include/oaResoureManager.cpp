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
  generateCube();
  generateCircle(36);
  generateCone(36);
  generateCone(36);
  generateCilinder(36);
  generateTorus(36,36,.5f);*/
  //loadDefaulTextures();
  loadDefaultShaders();
  generateDefaultShaderPrograms();
  generateDefaultMaterials();
  generateQuad();
  //generateTriangle();
  generateCube();
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

  quad->m_vertices = {
    Vertex{ Vector4f(-.5f,-.5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f,-.5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f, .5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f, .5f, 0.0f, 0.0f),Vector4f(0.0f,0.0f, 1.0f, 0.0f),Vector4f(1.0f,0.0f, 0.0f, 0.0f),Vector4f(0.0f,1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f) },
  };

  quad->m_index = {
    3,1,0,
    2,1,3,
  };

  quad->create();

  m_meshes.insert({ "quad",quad });

  auto modelQuad = makeSPtr<Model>();

  modelQuad->addMesh(quad);

  modelQuad->setName("quad");

  m_models.insert({ "quad",modelQuad });

  m_models["quad"]->setName("quad");
  m_models["quad"]->addMaterial(makeSPtr<Material>());

}

void
divide(const Plane& plane, Vector<Vector4f>& vertices, Vector<uint32>& index, Vector<uint32>& indexFront, Vector<uint32>& indexBack){
  
  Vector<Vector3f> newPoints;
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
    Triangle tri(vertices[index[i*3]].xyz,vertices[index[i*3+1]].xyz,vertices[index[i*3+2]].xyz);
    if(tri.separate(plane,newPoints,newIndexesFront,newIndexesBack,isFront)){
      replaceIndexes.push_back(index[i*3]);
      replaceIndexes.push_back(index[i*3+1]);
      replaceIndexes.push_back(index[i*3+2]);
      replaceIndexes.push_back(vertices.size());
      vertices.push_back(Vector4f(newPoints[0],0));
      replaceIndexes.push_back(vertices.size());
      vertices.push_back(Vector4f(newPoints[1],0));
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

  Vector<Vector4f> vertices = {
    /*Vertex{*/ Vector4f(-.5f, .5f, -.5f ,0.0f)/*,Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f( .5f, .5f, -.5f ,0.0f)/*,Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f( .5f, .5f,  .5f ,0.0f)/*,Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 1.0f)}*/,
    /*Vertex{*/ Vector4f(-.5f, .5f,  .5f ,0.0f)/*,Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 1.0f)}*/,
    /*       */                                /*                                                        */
    /*Vertex{*/ Vector4f(-.5f, -.5f, -.5f,0.0f)/*,Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f( .5f, -.5f, -.5f,0.0f)/*,Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f( .5f, -.5f,  .5f,0.0f)/*,Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)}*/,
    /*Vertex{*/ Vector4f(-.5f, -.5f,  .5f,0.0f)/*,Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)}*/,
    /*       */                                /*                                                        */
    /*Vertex{*/ Vector4f(-.5f, -.5f,  .5f,0.0f)/*, Vector4f(-1.0f,0.0f, 0.0f,0.0f), Vector2f(0.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f(-.5f, -.5f, -.5f,0.0f)/*,Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f)}*/,
    /*Vertex{*/ Vector4f(-.5f,  .5f, -.5f,0.0f)/*,Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f)}*/,
    /*Vertex{*/ Vector4f(-.5f,  .5f,  .5f,0.0f)/*,Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f)}*/,
    /*       */                                /*                                                        */
    /*Vertex{*/ Vector4f( .5f, -.5f,  .5f,0.0f)/*,Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f, -.5f, -.5f,0.0f)/*,Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f,  .5f, -.5f,0.0f)/*,Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 1.0f) }*/,
    /*Vertex{*/ Vector4f( .5f,  .5f,  .5f,0.0f)/*,Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 1.0f) }*/,
    /*       */                                /*                                                        */
    /*Vertex{*/ Vector4f(-.5f, -.5f, -.5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f, -.5f, -.5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f,  .5f, -.5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) }*/,
    /*Vertex{*/ Vector4f(-.5f,  .5f, -.5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) }*/,
    /*       */                                /*                                                        */
    /*Vertex{*/ Vector4f(-.5f, -.5f,  .5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f, -.5f,  .5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) }*/,
    /*Vertex{*/ Vector4f( .5f,  .5f,  .5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) }*/,
    /*Vertex{*/ Vector4f(-.5f,  .5f,  .5f,0.0f)/*,Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 1.0f) }*/,
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

  Octree tree;
  auto planes = tree.getPlanes();
  Vector<uint32> indexFront;
  Vector<uint32> indexBack;
  Vector<Vector<uint32>> meshes;
  meshes.push_back(index);
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

  for(int32 i = 0; i<8; ++i){
    String name = "cube"+StringUtilities::intToString(i);
    m_models.insert({name,makeSPtr<Model>()});
    auto& model = m_models[name];
    model->setName(name);
    model->addMaterial(makeSPtr<Material>());
    model->addMesh(makeSPtr<Mesh>());
    auto& mesh = model->getMesh(0);
    mesh->setIndex(meshes[i]);
    mesh->create(vertices.data(),sizeof(Vector4f),vertices.size());
  }

  

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

  Triangle tri(vertex[0].xyz,vertex[1].xyz,vertex[2].xyz);
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

void ResoureManager::loadDefaultShaders()
{
  auto& graphicsApi = GraphicAPI::instance();

  m_vertexShaders.insert({"default",graphicsApi.createVertexShader()});
  m_vertexShaders.insert({"animation",graphicsApi.createVertexShader()});
  m_vertexShaders.insert({"debug",graphicsApi.createVertexShader()});
  m_vertexShaders.insert({"screen",graphicsApi.createVertexShader()});
  m_vertexShaders.insert({"position",graphicsApi.createVertexShader()});

  m_pixelShaders.insert({"default",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"paralax",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"transparent",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"debug",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"GBuffer",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"lights",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"ssao",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"convolution",graphicsApi.createPixelShader()});
  m_pixelShaders.insert({"copy",graphicsApi.createPixelShader()});


   m_pixelShaders.insert({"color",graphicsApi.createPixelShader()});

  m_vertexShaders["default"]->compileFromFile("vertexShader");
  m_vertexShaders["default"]->setName("default");
  
  m_vertexShaders["animation"]->compileFromFile("animVertexShader");
  m_vertexShaders["animation"]->setName("animation");
  
  m_vertexShaders["debug"]->compileFromFile("vertexDebug");
  m_vertexShaders["debug"]->setName("debug");

  m_vertexShaders["screen"]->compileFromFile("screen");
  m_vertexShaders["screen"]->setName("screen");

  //m_vertexShaders["position"]->compileFromFile("position");
  //m_vertexShaders["position"]->setName("position");


  m_pixelShaders["default"]->compileFromFile("pixelShader");
  m_pixelShaders["default"]->setName("default");
  
  m_pixelShaders["paralax"]->compileFromFile("paralax");
  m_pixelShaders["paralax"]->setName("paralax");
  
  m_pixelShaders["transparent"]->compileFromFile("Gtransparent");
  m_pixelShaders["transparent"]->setName("transparent");
  
  m_pixelShaders["debug"]->compileFromFile("pixelDebug");
  m_pixelShaders["debug"]->setName("debug");
  
  m_pixelShaders["GBuffer"]->compileFromFile("GBuffer");
  m_pixelShaders["GBuffer"]->setName("GBuffer");

  m_pixelShaders["lights"]->compileFromFile("lights");
  m_pixelShaders["lights"]->setName("lights");

  m_pixelShaders["color"]->compileFromFile("color");
  m_pixelShaders["color"]->setName("color");

  m_pixelShaders["ssao"]->compileFromFile("ssao");
  m_pixelShaders["ssao"]->setName("ssao");

  m_pixelShaders["convolution"]->compileFromFile("convolution");
  m_pixelShaders["convolution"]->setName("convolution");

  m_pixelShaders["copy"]->compileFromFile("copy");
  m_pixelShaders["copy"]->setName("copy");
}

void ResoureManager::loadDefaulTextures()
{
  m_textures.insert({"default",GraphicAPI::instancePtr()->createTexture()});
  Path path;
  path.setCompletePath("textures/defaultTexture.png");
  //m_textures["default"]->loadFromFile(path);
}

void
ResoureManager::generateDefaultShaderPrograms()
{
  auto& graphicApi = GraphicAPI::instance();
  m_shaderPrograms.insert({"default",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"paralax",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"animation",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"transparent",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"debug",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"GBuffer",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"lights",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"color",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"ssao",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"convolution",graphicApi.createShaderProgram()});
  m_shaderPrograms.insert({"copy",graphicApi.createShaderProgram()});


  m_shaderPrograms["default"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["default"]->attach(m_pixelShaders["default"]);
  m_shaderPrograms["default"]->setName("default");
  
  m_shaderPrograms["animation"]->attach(m_vertexShaders["animation"]);
  m_shaderPrograms["animation"]->attach(m_pixelShaders["default"]);
  m_shaderPrograms["animation"]->setName("animation");
  
  m_shaderPrograms["paralax"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["paralax"]->attach(m_pixelShaders["paralax"]);
  m_shaderPrograms["paralax"]->setName("paralax");
  
  
  m_shaderPrograms["transparent"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["transparent"]->attach(m_pixelShaders["transparent"]);
  m_shaderPrograms["transparent"]->setName("transparent");
  m_shaderPrograms["transparent"]->setChannels({"diffuse","specular","normalMap"});

  
  m_shaderPrograms["debug"]->attach(m_vertexShaders["debug"]);
  m_shaderPrograms["debug"]->attach(m_pixelShaders["debug"]);
  m_shaderPrograms["debug"]->setName("debug");
  
  m_shaderPrograms["GBuffer"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["GBuffer"]->attach(m_pixelShaders["GBuffer"]);
  m_shaderPrograms["GBuffer"]->setName("GBuffer");
  m_shaderPrograms["GBuffer"]->setChannels({"diffuse","specular","normalMap"});

  m_shaderPrograms["lights"]->attach(m_vertexShaders["screen"]);
  m_shaderPrograms["lights"]->attach(m_pixelShaders["lights"]);
  m_shaderPrograms["lights"]->setName("lights");

  m_shaderPrograms["color"]->attach(m_vertexShaders["debug"]);
  m_shaderPrograms["color"]->attach(m_pixelShaders["color"]);
  m_shaderPrograms["color"]->setName("color");

  m_shaderPrograms["ssao"]->attach(m_vertexShaders["screen"]);
  m_shaderPrograms["ssao"]->attach(m_pixelShaders["ssao"]);
  m_shaderPrograms["ssao"]->setName("ssao");

  m_shaderPrograms["convolution"]->attach(m_vertexShaders["screen"]);
  m_shaderPrograms["convolution"]->attach(m_pixelShaders["convolution"]);
  m_shaderPrograms["convolution"]->setName("convolution");

  m_shaderPrograms["copy"]->attach(m_vertexShaders["screen"]);
  m_shaderPrograms["copy"]->attach(m_pixelShaders["copy"]);
  m_shaderPrograms["copy"]->setName("copy");
}

void 
ResoureManager::generateDefaultMaterials()
{
  //auto material = makeSPtr<Material>();
  //material->setName("debug");
  //material->setShader(m_shaderPrograms["debug"]);
  //m_materials.insert({material->getName(),material});
}

}

