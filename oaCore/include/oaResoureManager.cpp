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
#include "oaOctree.h"
#include "oaVertexBuffer.h"


namespace oaEngineSDK{

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

void
divide(const Plane& plane, Vector<Vertex>& vertices, Vector<uint32>& index, Vector<uint32>& indexFront, Vector<uint32>& indexBack){
  
  Vector<Vertex> newPoints;
  Vector<uint32> newIndexesFront;
  Vector<uint32> newIndexesBack;
  Vector<uint32> replaceIndexes;
  Vector<uint32> finalIndexesFront;
  Vector<uint32> finalIndexesBack;
  SIZE_T trisNum = index.size()/3;
  bool isFront;
  for(SIZE_T i = 0; i<trisNum; ++i){
    replaceIndexes.clear();
    newIndexesFront.clear();
    newIndexesBack.clear();
    newPoints.clear();
    Triangle tri(vertices[index[i*3]],vertices[index[i*3+1]],vertices[index[i*3+2]]);
    if(tri.separate(plane,newPoints,newIndexesFront,newIndexesBack,isFront)){
      replaceIndexes.push_back(index[i*3]);
      replaceIndexes.push_back(index[i*3+1]);
      replaceIndexes.push_back(index[i*3+2]);
      replaceIndexes.push_back(static_cast<uint32>(vertices.size()));
      vertices.push_back(newPoints[0]);
      replaceIndexes.push_back(static_cast<uint32>(vertices.size()));
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
  
 
  //String name = "cube";//+StringUtilities::intToString(i);
  //m_models.insert({name,makeSPtr<Model>()});
  //auto& model = m_models[name];
  //model->setName(name);
  //model->addMaterial(makeSPtr<Material>());
  //auto& material = model->getMaterial(0);
  //material->setShader(0);
  //m_materials.insert({"wall",material});
  //model->addMesh(makeSPtr<Mesh>());
  //auto& mesh = model->getMesh(0);
  //mesh->setIndex(index);
  //mesh->create(vertices.data(),sizeof(Vertex),vertices.size());
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
createHullShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createHullShader();
  resourceManager.m_hullShaders.insert({name,shader});
  shader->compileFromFile(name);
  shader->setName(name);
}

void 
createDomainShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createHullShader();
  resourceManager.m_hullShaders.insert({name,shader});
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
createShaderProgram(const String& name, const String& vertex,
                                        const String& hull,
                                        const String& domain,
                                        const String& pixel){
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto program = graphicsApi.createShaderProgram();
  resourceManager.m_shaderPrograms.insert({name,program});
  program->attach(resourceManager.m_vertexShaders[vertex]);
  program->attach(resourceManager.m_hullShaders[hull]);
  program->attach(resourceManager.m_domainShaders[domain]);
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
  //createVertexShader("position");

  createPixelShader("paralax");
  createPixelShader("transparent");
  //createPixelShader("debug");
  //createPixelShader("GBuffer");
  createPixelShader("lights");
  createPixelShader("ssao");
  createPixelShader("convolution");
  createPixelShader("copy");
  createPixelShader("color");
  createPixelShader("downSample");
  //createPixelShader("shadowMapper");
  //createPixelShader("directionalLight");
  //createPixelShader("pointLight");

  //createHullShader("hull");
  //createDomainShader("domain");

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

  shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({"spotLight",shader});
  shader->compileFromFile("light",{"SPOT"});
  shader->setName("spotLight");


  shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({"HBlur",shader});
  shader->compileFromFile("blur",{"HORIZONTAL"});
  shader->setName("HBlur");

  shader = graphicsApi.createPixelShader();
  resourceManager.m_pixelShaders.insert({"VBlur",shader});
  shader->compileFromFile("blur",{"VERTICAL"});
  shader->setName("VBlur");

  shader = graphicsApi.createHullShader();
  resourceManager.m_hullShaders.insert({"hullTris",shader});
  shader->compileFromFile("hull",{"TRIS"});
  shader->setName("hullTris");

  shader = graphicsApi.createHullShader();
  resourceManager.m_hullShaders.insert({"hullQuad",shader});
  shader->compileFromFile("hull",{"QUAD"});
  shader->setName("hullQuad");

  shader = graphicsApi.createDomainShader();
  resourceManager.m_domainShaders.insert({"domainQuad",shader});
  shader->compileFromFile("domain",{"QUAD"});
  shader->setName("domainQuad");

  shader = graphicsApi.createVertexShader();
  resourceManager.m_vertexShaders.insert({"Tesselation",shader});
  shader->compileFromFile("vertexShader",{"TESSEL"});
  shader->setName("Tesselation");

  shader = graphicsApi.createVertexShader();
  resourceManager.m_vertexShaders.insert({"SimpleVertex",shader});
  shader->compileFromFile("vertexShader",{"SIMPLE"});
  shader->setName("SimpleVertex");

  //createShaderProgram("default","vertexShader","default");
  //todo: cambiarlo a gbuffer
  //("animation","animVertexShader","default");
  createShaderProgram("paralax","vertexShader","paralax");
  createShaderProgram("transparent","vertexShader","transparent");
  m_shaderPrograms["transparent"]->setChannels({"diffuse","specular","normalMap"});
  createShaderProgram("debug","vertexDebug","debug");
  //createShaderProgram("GBuffer","vertexShader","GBuffer");
  //m_shaderPrograms["GBuffer"]->setChannels({"diffuse","specular","normalMap","emisive"});
  createShaderProgram("lights","screen","lights");
  //createShaderProgram("color","debug","color");
  createShaderProgram("ssao","screen","ssao");
  createShaderProgram("convolution","screen","convolution");
  createShaderProgram("copy","screen","copy");
  createShaderProgram("directionalLight","screen","directionalLight");
  createShaderProgram("pointLight","screen","pointLight");
  createShaderProgram("spotLight","screen","spotLight");
  createShaderProgram("HBlur","screen","HBlur");
  createShaderProgram("VBlur","screen","VBlur");
  createShaderProgram("downSample","screen","downSample");
  createShaderProgram("shadowMapper","SimpleVertex","color");
  createShaderProgram("Tesselator","Tesselation","hullQuad","domainQuad","color");
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

void
ResoureManager::separate(SPtr<Model> model,
                         const Vector3f& center, 
                         Vector<SPtr<Model>>& division,
                         float size)
{
  Vector<uint32> indexFront;
  Vector<uint32> indexBack;
  Vector<Vector<uint32>> meshes;
  Vector<Vector<uint32>> newMeshes;
  Vector<SPtr<Model>> newModels;
  Vector<uint32> finalIndex;
  Vector<Vertex> finalVertex;
  Octree tree(center);
  auto planes = tree.getPlanes();
  //print(StringUtilities::floatToString(center.x));
  //print(StringUtilities::floatToString(center.y));
  //print(StringUtilities::floatToString(center.z));
  
  for(int32 i = 0; i<8; ++i){
    String name = "model"+StringUtilities::intToString(i);
    auto newModel = makeSPtr<Model>();
    newModel->setName(name);
    newModels.push_back(newModel);
  }

  auto numOfMeshes = model->getNumOfMeshes();
  

  for(uint32 meshNum = 0; meshNum<numOfMeshes; ++meshNum){
    meshes.clear();

    auto mesh = model->getMesh(meshNum).lock();
    auto& material = model->getMaterial(meshNum);
    auto& indices = mesh->getIndex();
    auto vertices = mesh->getVertex();
    
    meshes.push_back(indices);

    for(auto& plane: planes){
      for(Vector<uint32>& m : meshes){
        indexBack.clear();
        indexFront.clear();
        divide(plane, vertices, m, indexBack, indexFront);
        newMeshes.push_back(indexBack);
        newMeshes.push_back(indexFront);
      }
      meshes = newMeshes;
      newMeshes.clear();
    }
    
    

   
    //auto  vertexB = GraphicAPI::instancePtr()->createVertexBuffer();
    //vertexB->init(vertices.data(),sizeof(Vertex),vertices.size());
    uint32 indexNum;
    for(uint32 i = 0; i<8; ++i){
      if(meshes[i].size()==0) continue;
      auto newModel = newModels[i];
      newModel->addMaterial(material);
      auto newMesh = makeSPtr<StaticMesh>();
      newModel->addMesh(newMesh);

      finalIndex.clear();
      finalVertex.clear();
      indexNum = 0;
      for(uint32 index : meshes[i]){
        finalVertex.push_back(vertices[index]);
        finalIndex.push_back(indexNum);
        ++indexNum;
      }

      newMesh->setIndex(finalIndex);
      newMesh->setVertex(finalVertex);
      newMesh->writeBuffers();
      //newMesh->create(vertexB);
    }
  }

  for(uint32 i = 0; i<8; ++i){

    SIZE_T totalTris = 0;
    for(uint32 meshNum = 0; meshNum<numOfMeshes; ++meshNum){
      auto mesh = model->getMesh(meshNum).lock();
      auto& indices = mesh->getIndex();
      totalTris += indices.size()/3;
    }
    if(totalTris>5000){
      auto newCenter = tree.getCenters(size);
      separate(newModels[i],newCenter[i],division,size/2.f);
    }
    else if(newModels[i]->getNumOfMeshes()>0){

      division.push_back(newModels[i]);
      print(newModels[i]->getName());
    }
  }
  
  
}

}

