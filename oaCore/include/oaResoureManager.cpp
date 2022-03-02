#include "oaResoureManager.h"
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
  //generateQuad();
  //loadDefaulTextures();
  loadDefaultShaders();
  generateDefaultShaderPrograms();
}
/*
void 
ResoureManager::generateCircle(const uint8 n)
{
  /*meshes.insert({ "circle",newSPtr<Mesh>() });
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
  /*meshes.insert({ "cone",newSPtr<Mesh>() });
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
  /*meshes.insert({ "cilinder",newSPtr<Mesh>() });
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
  /*meshes.insert({ "torus",newSPtr<Mesh>() });
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
  auto quad = newSPtr<StaticMesh>();

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

  auto modelQuad = newSPtr<Model>();

  modelQuad->addMesh(quad);

  modelQuad->m_name = "quad";

  m_models.insert({ "quad",modelQuad });

}

void 
ResoureManager::generateCube()
{
  /*meshes.insert({ "cube",newSPtr<Mesh>() });
  Vector<Vertex> vertices = {
    Vertex{ Vector4f(-.5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, .5f, -.5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f, .5f,  .5f ,0.0f), Vector4f(0.0f,1.0f,  0.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f, .5f,  .5f ,0.0f),Vector4f(0.0f,1.0f,   0.0f,0.0f), Vector2f(0.0f, 1.0f) },

    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,-1.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f) },

    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f), Vector4f(-1.0f,0.0f, 0.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(-1.0f,0.0f,  0.0f,0.0f), Vector2f(0.0f, 1.0f) },

    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(1.0f,0.0f,   0.0f,0.0f),Vector2f(0.0f, 1.0f) },

    Vertex{ Vector4f(-.5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f),Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f,  .5f, -.5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 1.0f) },

    Vertex{ Vector4f(-.5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 0.0f) },
    Vertex{ Vector4f( .5f, -.5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(1.0f, 0.0f) },
    Vertex{ Vector4f( .5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(1.0f, 1.0f) },
    Vertex{ Vector4f(-.5f,  .5f,  .5f,0.0f),Vector4f(0.0f,0.0f,  -1.0f,0.0f), Vector2f(0.0f, 1.0f) },
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

  meshes["cube"]->create(vertices,index);*/

}

void ResoureManager::loadDefaultShaders()
{
  m_vertexShaders.insert({"default",GraphicAPI::instancePtr()->createVertexShader()});
  m_vertexShaders.insert({"animation",GraphicAPI::instancePtr()->createVertexShader()});
  m_vertexShaders.insert({"debug",GraphicAPI::instancePtr()->createVertexShader()});
  m_pixelShaders.insert({"default",GraphicAPI::instancePtr()->createPixelShader()});
  m_pixelShaders.insert({"paralax",GraphicAPI::instancePtr()->createPixelShader()});
  m_pixelShaders.insert({"transparent",GraphicAPI::instancePtr()->createPixelShader()});
  m_pixelShaders.insert({"debug",GraphicAPI::instancePtr()->createPixelShader()});

  m_vertexShaders["default"]->compileFromFile("vertexShader");
  m_vertexShaders["animation"]->compileFromFile("animVertexShader");
  m_vertexShaders["debug"]->compileFromFile("vertexDebug");

  m_pixelShaders["default"]->compileFromFile("pixelShader");
  m_pixelShaders["paralax"]->compileFromFile("paralax");
  m_pixelShaders["transparent"]->compileFromFile("transparent");
  m_pixelShaders["debug"]->compileFromFile("pixelDebug");
  
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

  m_shaderPrograms["default"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["default"]->attach(m_pixelShaders["default"]);

  m_shaderPrograms["animation"]->attach(m_vertexShaders["animation"]);
  m_shaderPrograms["animation"]->attach(m_pixelShaders["default"]);

  m_shaderPrograms["paralax"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["paralax"]->attach(m_pixelShaders["paralax"]);

  m_shaderPrograms["transparent"]->attach(m_vertexShaders["default"]);
  m_shaderPrograms["transparent"]->attach(m_pixelShaders["transparent"]);

  m_shaderPrograms["debug"]->attach(m_vertexShaders["vertexDebug"]);
  m_shaderPrograms["debug"]->attach(m_pixelShaders["pixelDebug"]);

  /*m_materials.insert({"default",newSPtr<Material>()});
  m_materials.insert({"paralax",newSPtr<Material>()});
  m_materials.insert({"animation",newSPtr<Material>()});
  //m_materials["default"]->m_diffuse = m_textures["default"];
  
  m_materials["default"]->m_name = "default";
  
  m_materials["animation"]->m_program->attach(m_vertexShaders["animation"]);
  m_materials["animation"]->m_program->attach(m_pixelShaders["default"]);
  //m_materials["animation"]->m_diffuse = m_textures["default"];

  m_materials["animation"]->m_name = "animation";

  m_materials["paralax"]->m_program->attach(m_vertexShaders["default"]);
  m_materials["paralax"]->m_program->attach(m_pixelShaders["paralax"]);
  //m_materials["paralax"]->m_diffuse = m_textures["default"];

  m_materials["paralax"]->m_name = "paralax";*/
}

}

