#include "oaResoureManager.h"
#include <oaPlane.h>
#include <oaTriangle.h>
#include "oaGraphicAPI.h"
#include "oaTexture.h"
#include "oaModel.h"
#include "oaShader.h"
#include "oaMaterial.h"
#include "oaMesh.h"
#include "oaShaderProgram.h"
#include "oaOctree.h"
#include "oaVertexBuffer.h"
#include "oaAdaptativeShader.h"
#include "oaStaticMesh.h"

namespace oaEngineSDK{

void
ResoureManager::onStartUp()
{
  loadDefaultShaders();
}



void 
createVertexShader(const String& name){
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createVertexShader();
  resourceManager.registerResourse(name,shader);
  shader->compileFromFile(name);
}

void 
createPixelShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse(name,shader);
  shader->compileFromFile(name);
}

void 
createHullShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createHullShader();
  resourceManager.registerResourse(name,shader);
  shader->compileFromFile(name);
}

void 
createDomainShader(const String& name)
{
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createHullShader();
  resourceManager.registerResourse(name,shader);
  shader->compileFromFile(name);
}

void 
createShaderProgram(const String& name, const String& vertex, const String& pixel){
  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto program = graphicsApi.createShaderProgram();
  resourceManager.registerResourse(name,program);
  program->attach(cast<Shader>(resourceManager.getResourse(vertex)));
  program->attach(cast<Shader>(resourceManager.getResourse(pixel)));
}

void 
createShaderProgram(const String& name, const String& vertex,
                                        const String& hull,
                                        const String& domain,
                                        const String& pixel){
  //auto& graphicsApi = GraphicAPI::instance();
  //auto& resourceManager = ResoureManager::instance();
  //auto program = graphicsApi.createShaderProgram();
  //resourceManager.registerResourse(name,program);
  //program->attach(cast<Shader>(resourceManager.getResourse(vertex)));
  //program->attach(cast<Shader>(resourceManager.getResourse(hull)));
  //program->attach(cast<Shader>(resourceManager.getResourse(domain)));
  //program->attach(cast<Shader>(resourceManager.getResourse(pixel)));
  //program->setName(name);
}

void 
ResoureManager::loadDefaultShaders()
{
  deleteAllResoursesOfType(RESOURSE_TYPE::kShader);
  createVertexShader("v_vertexShader");
  createVertexShader("v_animVertexShader");
  createVertexShader("v_vertexDebug");
  createVertexShader("v_screen");
  //createVertexShader("position");

  createPixelShader("p_paralax");
  createPixelShader("p_transparent");
  //createPixelShader("debug");
  //createPixelShader("GBuffer");
  createPixelShader("p_lights");
  createPixelShader("p_ssao");
  createPixelShader("p_convolution");
  createPixelShader("p_copy");
  createPixelShader("p_color");
  createPixelShader("p_downSample");
  createPixelShader("p_add");
  //createPixelShader("shadowMapper");
  //createPixelShader("directionalLight");
  //createPixelShader("pointLight");

  //createHullShader("hull");
  //createDomainShader("domain");

  auto& graphicsApi = GraphicAPI::instance();
  auto& resourceManager = ResoureManager::instance();
  auto shader = graphicsApi.createPixelShader();

  resourceManager.registerResourse("p_ambientLight",shader);
  shader->compileFromFile("p_light",{});

  shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse("p_directionalLight",shader);
  shader->compileFromFile("p_light",{"DIRECTIONAL"});

  shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse("p_pointLight",shader);
  shader->compileFromFile("p_light",{"POINT"});

  shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse("p_spotLight",shader);
  shader->compileFromFile("p_light",{"SPOT"});


  shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse("p_HBlur",shader);
  shader->compileFromFile("p_blur",{"HORIZONTAL"});

  shader = graphicsApi.createPixelShader();
  resourceManager.registerResourse("p_VBlur",shader);
  shader->compileFromFile("p_blur",{"VERTICAL"});

  shader = graphicsApi.createHullShader();
  resourceManager.registerResourse("h_hullTris",shader);
  shader->compileFromFile("hull",{"TRIS"});

  shader = graphicsApi.createHullShader();
  resourceManager.registerResourse("p_hullQuad",shader);
  shader->compileFromFile("hull",{"QUAD"});

  shader = graphicsApi.createDomainShader();
  resourceManager.registerResourse("d_domainQuad",shader);
  shader->compileFromFile("domain",{"QUAD"});

  shader = graphicsApi.createVertexShader();
  resourceManager.registerResourse("v_Tesselation",shader);
  shader->compileFromFile("v_vertexShader",{"TESSEL"});

  shader = graphicsApi.createVertexShader();
  resourceManager.registerResourse("v_SimpleVertex",shader);
  shader->compileFromFile("v_SimpleVertex",{"SIMPLE"});
  shader->setName("v_SimpleVertex");

  //createShaderProgram("default","vertexShader","default");
  //todo: cambiarlo a gbuffer
  //("animation","animVertexShader","default");
  createShaderProgram("paralax","v_vertexShader","p_paralax");
  //createShaderProgram("transparent","v_vertexShader","p_transparent");
  //cast<ShaderProgram>(resourceManager.getResourse("transparent")).lock()->setChannels({"diffuse","specular","normalMap"});
  createShaderProgram("debug","v_vertexDebug","p_debug");
  //createShaderProgram("GBuffer","vertexShader","GBuffer");
  //m_shaderPrograms["GBuffer"]->setChannels({"diffuse","specular","normalMap","emisive"});
  createShaderProgram("lights","v_screen","p_lights");
  //createShaderProgram("color","debug","color");
  createShaderProgram("ssao","v_screen","p_ssao");
  createShaderProgram("convolution","v_screen","p_convolution");
  createShaderProgram("copy","v_screen","p_copy");
  createShaderProgram("ambientLight","v_screen","p_ambientLight");
  createShaderProgram("directionalLight","v_screen","p_directionalLight");
  createShaderProgram("pointLight","v_screen","p_pointLight");
  createShaderProgram("spotLight","v_screen","p_spotLight");
  createShaderProgram("HBlur","v_screen","p_HBlur");
  createShaderProgram("VBlur","v_screen","p_VBlur");
  createShaderProgram("downSample","v_screen","p_downSample");
  createShaderProgram("add","v_screen","p_add");
  createShaderProgram("shadowMapper","v_SimpleVertex","p_color");
  createShaderProgram("Tesselator","v_Tesselation","h_hullQuad","d_domainQuad","p_color");
  SPtr<AdaptativeShader> gBuffer = makeSPtr<AdaptativeShader>();
  gBuffer->compile("GBuffer",{"EMISIVE","SPECULAR","NORMALS","DIFFUSE"});
  resourceManager.registerResourse("gBuffer",gBuffer);
}

void ResoureManager::loadDefaulTextures()
{
  //m_textures.insert({"default",GraphicAPI::instancePtr()->createTexture()});
  //Path path;
  //path.setCompletePath("textures/defaultTexture.png");
  //m_textures["default"]->loadFromFile(path);
}

void 
ResoureManager::generateDefaultMaterials()
{
  m_defaultMaterial = makeSPtr<Material>();
  m_defaultMaterial->setShader(0);
  m_defaultMaterial->setName("defaultMaterial");

  m_defaultMaterial->setColor("diffuse",Color::CYAN);
}

String 
ResoureManager::getUniqueName(String name)
{
  uint64 id = StringUtilities::getStringId(name);
  
  if(m_resourses.find(id) == m_resourses.end()){
    //m_ids.insert(id);
    return name;
  }
  else{
    int n = 2;
    name = name+"_";
    while(m_resourses.find(StringUtilities::getStringId(name+StringUtilities::intToString(n))) != m_resourses.end()){
      ++n;
    }
    return name+StringUtilities::intToString(n);
  }
}

void
ResoureManager::deleteResourse(const String& name)
{
  uint64 id = StringUtilities::getStringId(name);
  if(m_resourses.find(id) == m_resourses.end()){
    return;
  }
  auto resourse = m_resourses[id];
  auto& type = m_types[resourse->getType()];
  auto it = type.begin();
  for(; it != type.end(); ++it){
    if(it->lock().get() == resourse.get()){
      break;
    }
  }
  if(it != type.end()){
    type.erase(it);
  }
  m_resourses.erase(id);
}

void 
ResoureManager::changeName(const String& name, const String& newName)
{
  auto resourse = getResourse(name);
  deleteResourse(name);
  registerResourse(newName,resourse.lock());
}


}






/*
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
ResoureManager::separate(SPtr<Model> model,
                         const Vector3f& center, 
                         Vector<SPtr<Model>>& division,
                         float size)
{
  //Vector<uint32> indexFront;
  //Vector<uint32> indexBack;
  //Vector<Vector<uint32>> meshes;
  //Vector<Vector<uint32>> newMeshes;
  //Vector<SPtr<Model>> newModels;
  //Vector<uint32> finalIndex;
  //Vector<Vertex> finalVertex;
  //Octree tree(center);
  //auto planes = tree.getPlanes();
  ////print(StringUtilities::floatToString(center.x));
  ////print(StringUtilities::floatToString(center.y));
  ////print(StringUtilities::floatToString(center.z));
  //
  //for(int32 i = 0; i<8; ++i){
  //  String name = "model"+StringUtilities::intToString(i);
  //  auto newModel = makeSPtr<Model>();
  //  newModel->setName(name);
  //  newModels.push_back(newModel);
  //}
  //
  //auto numOfMeshes = model->getNumOfMeshes();
  //
  //
  //for(uint32 meshNum = 0; meshNum<numOfMeshes; ++meshNum){
  //  meshes.clear();
  //
  //  auto mesh = model->getMesh(meshNum).lock();
  //  auto& material = model->getMaterial(meshNum);
  //  auto& indices = mesh->getIndex();
  //  auto vertices = mesh->getVertex();
  //  
  //  meshes.push_back(indices);
  //
  //  for(auto& plane: planes){
  //    for(Vector<uint32>& m : meshes){
  //      indexBack.clear();
  //      indexFront.clear();
  //      divide(plane, vertices, m, indexBack, indexFront);
  //      newMeshes.push_back(indexBack);
  //      newMeshes.push_back(indexFront);
  //    }
  //    meshes = newMeshes;
  //    newMeshes.clear();
  //  }
  //  
  //  
  //
  // 
  //  //auto  vertexB = GraphicAPI::instancePtr()->createVertexBuffer();
  //  //vertexB->init(vertices.data(),sizeof(Vertex),vertices.size());
  //  uint32 indexNum;
  //  for(uint32 i = 0; i<8; ++i){
  //    if(meshes[i].size()==0) continue;
  //    auto newModel = newModels[i];
  //    newModel->addMaterial(material);
  //    auto newMesh = makeSPtr<StaticMesh>();
  //    newModel->addMesh(newMesh);
  //
  //    finalIndex.clear();
  //    finalVertex.clear();
  //    indexNum = 0;
  //    for(uint32 index : meshes[i]){
  //      finalVertex.push_back(vertices[index]);
  //      finalIndex.push_back(indexNum);
  //      ++indexNum;
  //    }
  //
  //    newMesh->setIndex(finalIndex);
  //    newMesh->setVertex(finalVertex);
  //    newMesh->writeBuffers();
  //    //newMesh->create(vertexB);
  //  }
  //}
  //
  //for(uint32 i = 0; i<8; ++i){
  //
  //  SIZE_T totalTris = 0;
  //  for(uint32 meshNum = 0; meshNum<numOfMeshes; ++meshNum){
  //    auto mesh = model->getMesh(meshNum).lock();
  //    auto& indices = mesh->getIndex();
  //    totalTris += indices.size()/3;
  //  }
  //  if(totalTris>5000){
  //    auto newCenter = tree.getCenters(size);
  //    separate(newModels[i],newCenter[i],division,size/2.f);
  //  }
  //  else if(newModels[i]->getNumOfMeshes()>0){
  //
  //    division.push_back(newModels[i]);
  //    print(newModels[i]->getName());
  //  }
  //}
  
  
}

*/