#include "oaOmniverse.h"
#include <oaActor.h>
#include <oaStaticMesh.h>
#include <oaModel.h>
#include <oaResoureManager.h>
#include <oaActor.h>
#include <OmniClient.h>
#include <LiveSessionInfo.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/base/gf/vec3f.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/cube.h>
#include "pxr/usd/usdShade/materialBindingAPI.h"
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>
#include <oaActor.h>
#include <oaStaticMeshComponent.h>
#include <oaModel.h>
#include <oaMesh.h>
#include <oaResoureManager.h>
#include <oaMaterial.h>
#include <oaTransform.h>
#include <oaLoader.h>
#include <oaResoureManager.h>
#include <oaStaticMeshComponent.h>
#include <oaTexture.h>
#include <oaDirectionalLightComponent.h>
#include <oaPointLightComponent.h>
#include <oaSpotLightComponent.h>

namespace oaEngineSDK 
{

String g_myPath = "C:/Users/roriv/Documents/GitHub/oasisEngine/bin/omniverse/";
String g_omniversePath;
PXR_NAMESPACE_USING_DIRECTIVE

TF_DEFINE_PRIVATE_TOKENS(
	_tokens,
	(box)
    (DistantLight)
    (DomeLight)
    (Looks)
    (Root)
    (Shader)
    (st)

    // These tokens will be reworked or replaced by the official MDL schema for USD.
    // https://developer.nvidia.com/usd/MDLschema
    (Material)
    ((_module, "module"))
    (name)
    (out)
    ((shaderId, "mdlMaterial"))
    (mdl)

    // Tokens used for USD Preview Surface
    (diffuseColor)
    (normal)
    (file)
    (result)
    (varname)
    (rgb)
    (RAW)
    (sRGB)
    (surface)
    (PrimST)
    (UsdPreviewSurface)
    ((UsdShaderId, "UsdPreviewSurface"))
    ((PrimStShaderId, "UsdPrimvarReader_float2"))
    (UsdUVTexture)
);

using std::fill;

PXR_NAMESPACE_USING_DIRECTIVE

UsdStageRefPtr g_stage = nullptr;
LiveSessionInfo g_liveSessionInfo;
void
uploadCallback(void* userData, OmniClientResult result)
{
  print(StringUtilities::intToString(result));
}
void checkPointsCallBack(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
{
  if(numEntries==0) return;
  auto entry = entries[numEntries-1].relativePath;
  auto& textures = reinterpret_cast<Omniverse*>(Omniverse::instancePtr())->m_textures;
  int i;
  for (i = 0; entry[i] != '='; ++i);
  ++i;
  String sNum;
  for (; entry[i] != '\0'; ++i){
    sNum +=entry[i];
  }
  int num = atoi(sNum.c_str());
  if(num != textures[(int)userData].checkPoint){
    textures[(int)userData].checkPoint = num;
    omniClientWait(omniClientCopy(textures[*((int*)userData)].omniverseDir.string().c_str(),textures[*((int*)userData)].dir.string().c_str(),nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }
}

static void logCallback(const char* threadName, const char* component, OmniClientLogLevel level, const char* message) noexcept
{
    print(message);
}


void 
Omniverse::onStartUp()
{
  omniClientSetLogCallback(logCallback);
  
  if (!omniClientInitialize(kOmniClientVersion)){
    print("omniverse not working");
    return;
  }
}

void 
Omniverse::onShutDown()
{
  omniClientLiveWaitForPendingUpdates();

  g_stage.Reset();

  omniClientShutdown();
}

bool 
Omniverse::connect()
{
  String destinationPath;
  if (destinationPath == "")
  {
    //m_userFolder = "omniverse://192.168.138.220/Users";
    m_userFolder = "omniverse://localhost/Users";
    m_userName = getConnectedUsername();
    g_omniversePath = m_destinationPath = m_userFolder + "/" + m_userName;
  }
  //auto sessionList = g_liveSessionInfo.GetLiveSessionList();
  //
  ////print(liveSessionUrl);
  //print("secions");
  //for (auto& secion : sessionList){
  //  print(secion);
  //}

  //g_liveSessionInfo.SetSessionName(sessionName.c_str());
  return true;
}

String
Omniverse::getConnectedUsername()
{
  std::string userName = "_none_";
  omniClientWait(omniClientGetServerInfo(m_userFolder.c_str(), &userName, [](void* userData, OmniClientResult result, struct OmniClientServerInfo const * info) noexcept
  {
    std::string* userName = static_cast<std::string*>(userData);
    if (userData && userName && info && info->username)
    {
        userName->assign(info->username);
    }
  }));

  return userName;
}

void 
Omniverse::createModel(const String& name, WPtr<Actor> actor)
{
  m_stageUrl = m_destinationPath + "/" + name;//+(doLiveEdit ? ".live" : ".usd");
  
  print("Waiting for " + m_stageUrl + " to delete... ");
  omniClientWait(omniClientDelete(m_stageUrl.c_str(), nullptr, nullptr));
  print("finished");
  
  g_stage = UsdStage::CreateNew(m_stageUrl);
  if (!g_stage){
      print("Failure to create model in Omniverse");
      print(m_stageUrl.c_str());
      return;
  }
  else {
      print("New stage created: " + m_stageUrl);
  }
  addScene(actor);
}

bool _is_binding_stronger_than_descendents(
    pxr::UsdShadeMaterialBindingAPI const &binding,
    pxr::TfToken const &purpose
) {
    static pxr::TfToken const strength {"strongerThanDescendents"};

    return pxr::UsdShadeMaterialBindingAPI::GetMaterialBindingStrength(
        binding.GetDirectBindingRel(purpose)) == strength;
}


bool _is_collection_binding_stronger_than_descendents(
    pxr::UsdShadeMaterialBindingAPI::CollectionBinding const &binding
) {
    static pxr::TfToken const strength {"strongerThanDescendents"};

    return pxr::UsdShadeMaterialBindingAPI::GetMaterialBindingStrength(
        binding.GetBindingRel()) == strength;
}

auto _get_collection_material_bindings_for_purpose(
    UsdShadeMaterialBindingAPI const &binding,
    TfToken const &purpose
) -> Vector<UsdShadeMaterialBindingAPI::CollectionBinding> {
  auto parent = binding.GetPrim();
  
  for (; not parent.IsPseudoRoot(); parent = parent.GetParent()) {
    auto binding = pxr::UsdShadeMaterialBindingAPI {parent};
  
    // TODO: Check if this function works in C++
    // XXX : Note, Normally I'd just do
    // `UsdShadeMaterialBindingAPI.GetCollectionBindings` but, for
    // some reason, `binding.GetCollectionBindings(purpose)` does not
    // yield the same result as parsing the relationships, manually.
    // Maybe it's a bug?
    //
    // auto material_bindings = binding.GetCollectionBindings(purpose);
    //
    Vector<UsdShadeMaterialBindingAPI::CollectionBinding> material_bindings;
    auto bindings = binding.GetCollectionBindingRels(purpose);
  
    if (bindings.empty()) {
      continue;
    }
  
    material_bindings.reserve(bindings.size());
  
    for (auto const &relationship : bindings) {
      if (relationship.IsValid()) {
        material_bindings.emplace_back(relationship);
      }
    }
  
    if (!material_bindings.empty()) {
      return material_bindings;
    }
  }
  
  return {};
}

UsdShadeMaterial _get_direct_bound_material_for_purpose(
  UsdShadeMaterialBindingAPI const &binding,
  TfToken const &purpose
) 
{
  auto relationship = binding.GetDirectBindingRel(purpose);
  auto direct = UsdShadeMaterialBindingAPI::DirectBinding {relationship};

  if (!direct.GetMaterial()) {
      return UsdShadeMaterial {};
  }

  auto material = direct.GetMaterialPath();
  auto prim = binding.GetPrim().GetStage()->GetPrimAtPath(material);

  if (!prim.IsValid()) {
      return UsdShadeMaterial {};
  }

  return UsdShadeMaterial {prim};
}

UsdShadeMaterial get_bound_material(
  UsdPrim const &prim,
  TfToken material_purpose = UsdShadeTokens->allPurpose,
  String const &collection = ""
) 
{
  if (!prim.IsValid()) {
      print("prim \"" + prim.GetPath().GetString() + "\" is not valid");
  }


  std::set<pxr::TfToken> purposes = {material_purpose, pxr::UsdShadeTokens->allPurpose};
  pxr::UsdPrim parent;

  for (auto const &purpose : purposes) {
    pxr::UsdShadeMaterial material;

    for (parent = prim; not parent.IsPseudoRoot(); parent = parent.GetParent()) {
      auto binding = pxr::UsdShadeMaterialBindingAPI {parent};

      if (!material || _is_binding_stronger_than_descendents(binding, purpose)) {
        material = _get_direct_bound_material_for_purpose(binding, purpose);
      }

      for (auto const &collection_binding : _get_collection_material_bindings_for_purpose(binding, purpose)) {
        auto binding_collection = collection_binding.GetCollection();

        if (!collection.empty() && binding_collection.GetName() != collection) {
          continue;
        }

        auto membership = binding_collection.ComputeMembershipQuery();

        if (membership.IsPathIncluded(parent.GetPath()) && (!material || _is_collection_binding_stronger_than_descendents(collection_binding))) {
          material = collection_binding.GetMaterial();
        }
      }
    }

    if (material) {
      return material;
    }
  }

  return pxr::UsdShadeMaterial {};
}

void
readMLD(SPtr<Material> material, String path, String dotPath){
  FStream file;
  file.open(path);
  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
  auto tokens = StringUtilities::split(str," \n");
  auto numOfTokens = tokens.size();
  for(SIZE_T i = 0; i<numOfTokens; ++i){
    if(tokens[i] == "diffuse_texture:"){
      auto splited = StringUtilities::split(tokens[i+1],"\"");
      if(splited.size()>1){
        auto texturePath = splited[1];
        auto texturePathSize = texturePath.size();
        auto myPath = g_myPath;
        for(int i = 1;i<texturePathSize; ++i){
          dotPath+=texturePath[i];
        }
        for(int i = 2;i<texturePathSize; ++i){
          myPath+=texturePath[i];
        }
        print("texturePath->"+dotPath);
        char* data = new char[256];
        OmniClientRequestId res = omniClientCopy(dotPath.c_str(),myPath.c_str(),data,OmniClientCopyCallback(),eOmniClientCopy_ErrorIfExists);
        //print(omniClientGetResultString(OmniClientResult(res)));
        reinterpret_cast<Omniverse*>(Omniverse::instancePtr())->m_textures.push_back({dotPath,myPath,1});
        Loader loader;
        print("mytexturePath->"+myPath);
        Path p = Path(myPath);
        loader.loadResource(p,WPtr<Actor>());
        auto texture = cast<Texture>(ResoureManager::instance().getResourse(p.stem().string()));

        if(!texture.expired())
        material->setTexture("diffuse",texture);
      }
      
    }
    else if(tokens[i] == "normalmap_texture:"){
      auto splited = StringUtilities::split(tokens[i+1],"\"");
      if(splited.size()>1){
        auto texturePath =splited[1];
        auto texturePathSize = texturePath.size();
        auto myPath = g_myPath;
        for(int i = 1;i<texturePathSize; ++i){
          dotPath+=texturePath[i];
        }
        for(int i = 2;i<texturePathSize; ++i){
          myPath+=texturePath[i];
        }
        print("texturePath->"+dotPath);
        char* data = new char[256];
        OmniClientRequestId res = omniClientCopy(dotPath.c_str(),myPath.c_str(),data,OmniClientCopyCallback(),eOmniClientCopy_ErrorIfExists);
        print(omniClientGetResultString(OmniClientResult(res)));
        Loader loader;
        print("mytexturePath->"+myPath);
        Path p = Path(myPath);
        loader.loadResource(p,WPtr<Actor>());
        auto texture = cast<Texture>(ResoureManager::instance().getResourse(p.stem().string()));
        if(!texture.expired())
        material->setTexture("normalMap",texture);
        break;
      }
    }
  }
}

void 
loadMaterial(SPtr<Material> mat,UsdShadeMaterial& material)
{
  auto schema = material.GetSchemaAttributeNames();
  print("begin");
  for(auto token : schema){
    print(token.GetString());
  }
  print("end");

  SdfPathVector paths;
  //material.GetSurfaceOutput().get(&paths);
  for(auto path : paths){
    print(path.GetString());
  }
  //.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier")
  if(!material.GetPrim().IsValid()) return;
  auto shaders = material.GetPrim().GetChildren();
  if(shaders.empty()) return;
  for(auto child : shaders){
    auto shader = UsdShadeShader(child);
    auto source = shader.GetPrim().GetAttribute(TfToken("info:mdl:sourceAsset"));
    VtValue val;
    source.Get(&val);
    auto p = val.Get<SdfAssetPath>();
    auto assetPath = p.GetAssetPath();
    auto resolvedPath = p.GetResolvedPath();
    if(resolvedPath.size()==0){
      continue;
    }
    String dotPath;
    auto dif = resolvedPath.size()-assetPath.size()+2;

    auto myPath = g_myPath;

    for(int i = 0; i< dif; ++i){
      dotPath+=resolvedPath[i];
    }

    for(int i = 2; i< dif; ++i){
      if(assetPath[i]=='/') break;
      dotPath+=assetPath[i];
    }
    for(int i = 2; i< assetPath.size(); ++i){
      myPath+=assetPath[i];
    }

    print("myPath->"+myPath);
    print("matPath->"+String(p.GetResolvedPath().c_str()));
    char* data = new char[256];
    auto res = omniClientCopy(p.GetResolvedPath().c_str(),myPath.c_str(),data,OmniClientCopyCallback(),eOmniClientCopy_Overwrite);
    reinterpret_cast<Omniverse*>(Omniverse::instancePtr())->m_textures.push_back({Path(p.GetResolvedPath()),myPath,1});

    print(omniClientGetResultString(OmniClientResult(res)));
    readMLD(mat,myPath.c_str(),dotPath);
  }
  
}

void
loadMeshFromUSD(UsdGeomMesh UGmesh, WPtr<Actor> wActor,const String& name)
{
  auto& resourceManager = ResoureManager::instance();

  auto actor = wActor.lock();
  auto gc = makeSPtr<StaticMeshComponent>();
  actor->attachComponent(gc);
  auto existingModel = resourceManager.getResourse(name);
  if(!existingModel.expired()){
    gc->setModel(cast<Model>(existingModel));
    return;
  }

  
  auto model = makeSPtr<Model>();
  auto mesh = makeSPtr<StaticMesh>();
  //auto newMaterial = resourceManager.m_defaultMaterial;

  auto newMaterial = makeSPtr<Material>();
  newMaterial->setShader(0);
  resourceManager.registerResourse(name,mesh);
  resourceManager.registerResourse("m_"+name,model);
  resourceManager.registerResourse("mat_"+name,newMaterial);
  model->setMesh(mesh);
  model->setMaterial(newMaterial);
  gc->setModel(model);
  
  VtValue value;
  UGmesh.GetPointsAttr().Get(&value);
  auto points = value.Get<VtArray<GfVec3f>>();
  UGmesh.GetNormalsAttr().Get(&value);
  auto normals = value.Get<VtArray<GfVec3f>>();
  UGmesh.GetPrimvar(_tokens->st).GetAttr().Get(&value);
  auto uvs = value.Get<VtVec2fArray>();
  UGmesh.GetFaceVertexIndicesAttr().Get(&value);
  auto indices = value.Get<VtArray<int>>();
  UGmesh.GetFaceVertexCountsAttr().Get(&value);
  auto faceCount = value.Get<VtArray<int>>();

  SIZE_T numOfVertex = points.size();
  mesh->setVertexNum(numOfVertex);
  for(SIZE_T i=0; i<numOfVertex; ++i){
    mesh->setVertexAt(i,Vertex(
      Vector4f(points[i].data()[0],points[i].data()[1],points[i].data()[2],1.0f),
      Vector4f(normals[i].data()[0],normals[i].data()[1],normals[i].data()[2],0.0f),
      Vector2f(1.f-uvs[i].data()[0],1.f-uvs[i].data()[1])));
  }

  SIZE_T numOfIndices = indices.size();
  SIZE_T numOfFaces = faceCount.size();
  uint64 currectIndex = 0;
  //mesh->setIndexNum(numOfIndices);
  auto& index = mesh->getIndex();
  for(SIZE_T i=0; i<numOfFaces; ++i){
    index.push_back(indices[currectIndex]);
    index.push_back(indices[currectIndex+1]);
    index.push_back(indices[currectIndex+2]);
    
    if(faceCount[i] == 4){
      index.push_back(indices[currectIndex+2]);
      index.push_back(indices[currectIndex+3]);
      index.push_back(indices[currectIndex]);
      ++currectIndex;
    }
    currectIndex+=3;
  }
  mesh->writeBuffers();

  UsdShadeTokens->allPurpose;

  auto mat = get_bound_material(UGmesh.GetPrim());

  loadMaterial(newMaterial,mat);
}

void
loadDirectionalLight(UsdLuxDistantLight ULight, WPtr<Actor> wActor)
{
  auto actor = wActor.lock();
  auto component = makeSPtr<DirectionalLightComponent>();
  actor->attachComponent(component);
  VtValue value;
  ULight.GetColorAttr().Get(&value);
  auto color = value.Get<GfVec3f>();
  component->m_light.color = Color(color.GetArray()[0],color.GetArray()[1],color.GetArray()[2]);
  Vector3f rot;
  bool resetXformStack = true;
  Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        GfVec3f rotation(0);
        xFormOp.Get(&rotation);
        rot = Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]);
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        GfVec3d rotation(0);
        xFormOp.Get(&rotation);
        rot = Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]);
      }
    }
  }
  rot = rot/180.f*Math::PI;
  component->m_light.direction = Matrix4f::rotationMatrix(rot)*Vector4f(1,0,0,0);
}

void
loadPointLight(UsdLuxSphereLight ULight, WPtr<Actor> wActor)
{
  auto actor = wActor.lock();
  auto component = makeSPtr<PointLightComponent>();
  actor->attachComponent(component);
  VtValue value;
  ULight.GetColorAttr().Get(&value);
  auto color = value.Get<GfVec3f>();
  component->m_light.color = Color(color.GetArray()[0],color.GetArray()[1],color.GetArray()[2]);
  ULight.GetIntensityAttr().Get(&value);
  component->m_light.intensity = value.Get<float>();
  Vector3f pos;
  bool resetXformStack = true;
  Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        GfVec3f position(0);
        xFormOp.Get(&position);
        pos = Vector3f(position.data()[0],position.data()[1],position.data()[2]);
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        GfVec3d position(0);
        xFormOp.Get(&position);
        pos = Vector3f(position.data()[0],position.data()[1],position.data()[2]);
      }
    }
  }
  component->m_light.location = pos;
}

void
loadSpotLight(UsdLuxDiskLight ULight, WPtr<Actor> wActor)
{
  //auto actor = wActor.lock();
  //auto component = makeSPtr<SpotLightComponent>();
  //actor->attachComponent(component);
  //VtValue value;
  //ULight.GetColorAttr().Get(&value);
  //auto color = value.Get<GfVec3f>();
  //component->m_light.color = Color(color.GetArray()[0],color.GetArray()[1],color.GetArray()[2]);
  //ULight.GetIntensityAttr().Get(&value);
  //component->m_light.intensity = value.Get<float>();
  //ULight.GetSha
  //component->m_light.angle =
  //Vector3f pos;
  // Vector3f rot;
  //bool resetXformStack = true;
  //Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  //for(auto& xFormOp: xFormOps){
  //  if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
  //    if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
  //      GfVec3f position(0);
  //      xFormOp.Get(&position);
  //      pos = Vector3f(position.data()[0],position.data()[1],position.data()[2]);
  //    }
  //    else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
  //      GfVec3d position(0);
  //      xFormOp.Get(&position);
  //      pos = Vector3f(position.data()[0],position.data()[1],position.data()[2]);
  //    }
  //  }
  //
  //  else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
  //    if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
  //      GfVec3f rotation(0);
  //      xFormOp.Get(&rotation);
  //      rot = Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]);
  //    }
  //    else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
  //      GfVec3d rotation(0);
  //      xFormOp.Get(&rotation);
  //      rot = Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]);
  //    }
  //  }
  //}
  //component->m_light.location = pos;
  //rot = rot/180.f*Math::PI;
  //component->m_light.direction = (Matrix4f::rotationMatrix(rot)*Vector4f(1,0,0,0)).xyz;
  
}

void
loadActor(SPtr<Actor> parent, UsdPrim node)
{
  auto newActor = makeSPtr<Actor>();
  parent->attach(newActor);
  newActor->setName(node.GetName());

  UsdGeomXform xForm = UsdGeomXform(node);
  bool resetXformStack = true;
  Vector<UsdGeomXformOp> xFormOps = xForm.GetOrderedXformOps(&resetXformStack);
  
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        GfVec3f position(0);
        xFormOp.Get(&position);
        newActor->setActorLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        GfVec3d position(0);
        xFormOp.Get(&position);
        newActor->setActorLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
      }
      
    }
    else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        GfVec3f scale(0);
        xFormOp.Get(&scale);
        newActor->setActorScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        GfVec3d scale(0);
        xFormOp.Get(&scale);
        newActor->setActorScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
      }
    }
    else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        GfVec3f rotation(0);
        xFormOp.Get(&rotation);
        newActor->setActorRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        GfVec3d rotation(0);
        xFormOp.Get(&rotation);
        newActor->setActorRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
      }
    }
  }
  auto range = node.GetChildren();
	for (const auto& child : range)
	{
    if (child.IsA<UsdGeomMesh>()){
      loadMeshFromUSD(UsdGeomMesh(child),newActor,child.GetName().GetString());
    }
    else if(child.IsA<UsdLuxDistantLight>()){
      loadDirectionalLight(UsdLuxDistantLight(child),newActor);
    }
    else if(child.IsA<UsdLuxSphereLight>()){
      loadPointLight(UsdLuxSphereLight(child),newActor);
    }
    //else if(child.IsA<UsdLuxDiskLight>()){
    //  auto component = makeSPtr<SpotLightComponent>();
    //  newActor->attachComponent(component);
    //}
		else if (child.IsA<UsdGeomXform>())
		{
			print("Found UsdActor: " + child.GetName().GetString() );
      loadActor(newActor,child);
		}
	}
}

void 
Omniverse::connectToModel(const String& name, WPtr<Actor> wScene)
{
  m_stageUrl = m_destinationPath + "/" + name;
  m_scene = wScene;
  auto scene = wScene.lock();
  
  g_stage = UsdStage::Open(m_stageUrl);
  if (!g_stage){
    print("Failure to connect to model in Omniverse");
    print(m_stageUrl.c_str());
    return;
  }
  else {
    print("connected to: " + m_stageUrl);
  }
  SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
  UsdGeomXform rootPrim = UsdGeomXform::Define(g_stage, rootPrimPath);

  auto range = g_stage->Traverse();
	for (const auto& node : range)
	{
		if (node.IsA<UsdGeomXform>())
		{
			print("Found UsdActor: " + node.GetName().GetString() );

      //loadActor(scene,node);
      auto childs = node.GetChildren();
	    for (const auto& child : childs)
	    {
        if (child.IsA<UsdGeomXform>())
	    	{
	    		print("Found UsdActor: " + child.GetName().GetString() );
          loadActor(scene,child);
	    	}
	    }
    }
    break;
	}

}



void 
Omniverse::createMDL(SPtr<Resourse> resourse)
{
  auto material = cast<Material>(resourse);
  
  auto matName = material->getName();
  auto wTexture = material->getTexture("diffuse");
  auto wNormal = material->getTexture("normalMap");
  String textureAttr  = "";
  String normalAttr  = "";
  if(!wTexture.expired()){
    auto texture = wTexture.lock();
    String omniversePathTexture =  "./textures/"+texture->getPath().filename().string();
    textureAttr = "\"" + omniversePathTexture + "\", ::tex::gamma_srgb";
    omniClientWait(omniClientCopy(texture->getPath().string().c_str(),omniversePathTexture.c_str(),nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }
  if(!wNormal.expired()){
    auto normal = wNormal.lock();
    String omniversePathTexture =  "./textures/"+normal->getPath().filename().string();
    normalAttr = "\"" + omniversePathTexture + "\", ::tex::gamma_linear";
    omniClientWait(omniClientCopy(normal->getPath().string().c_str(),omniversePathTexture.c_str(),nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }
  auto fileName = g_myPath+"materials/"+matName+".mdl";
  ofstream outfile (fileName);
  String omniversePathMaterial =   g_omniversePath + "/files/materials/"+matName+".mdl";
  outfile << "mdl 1.4;\n"
    "import ::OmniPBR::OmniPBR;\n"
    "import ::anno::author;\n"
    "import ::anno::description;\n"
    "import ::anno::display_name;\n"
    "import ::anno::key_words;\n"
    "import ::anno::version;\n"
    "import ::tex::gamma_mode;\n"
    "import ::state::normal;\n"
    "\n"
    "export material "<<matName<<"(*)\n"
    "[[\n"
    "    ::anno::display_name(\"Omni PBR \"),\n"
    "    ::anno::description(\"Omni PBR, supports ORM textures\"),\n"
    "    ::anno::version(1, 0, 0, \"\"),\n"
    "    ::anno::author(\"NVIDIA CORPORATION\"),\n"
    "    ::anno::key_words(string[](\"omni\", \"PBR\", \"omniverse\", \"generic\"))\n"
    "]]\n"
    " = ::OmniPBR::OmniPBR(\n"
    "    diffuse_color_constant: color(0.200000003f, 0.200000003f, 0.200000003f),\n"
    "    diffuse_texture: texture_2d("<<textureAttr<<"),\n"
    "    albedo_desaturation: 0.f,\n"
    "    albedo_add: 0.f,\n"
    "    albedo_brightness: 1.f,\n"
    "    diffuse_tint: color(1.f, 1.f, 1.f),\n"
    "    reflection_roughness_constant: 0.5f,\n"
    "    reflection_roughness_texture_influence: 1.f,\n"
    "    reflectionroughness_texture: texture_2d(),\n"
    "    metallic_constant: 0.f,\n"
    "    metallic_texture_influence: 1.f,\n"
    "    metallic_texture: texture_2d(),\n"
    "    specular_level: 0.5f,\n"
    "    enable_ORM_texture: true,\n"
    "    ORM_texture: texture_2d(),\n"
    "    ao_to_diffuse: 0.f,\n"
    "    ao_texture: texture_2d(),\n"
    "    enable_emission: false,\n"
    "    emissive_color: color(1.f, 0.100000001f, 0.100000001f),\n"
    "    emissive_mask_texture: texture_2d(),\n"
    "    emissive_intensity: 40.f,\n"
    "    bump_factor: 1.f,\n"
    "    normalmap_texture: texture_2d("<<normalAttr<<"),\n"
    "    detail_bump_factor: 0.300000012f,\n"
    "    detail_normalmap_texture: texture_2d(),\n"
    "    project_uvw: false,\n"
    "    world_or_object: false,\n"
    "    uv_space_index: 0,\n"
    "    texture_translate: float2(0.f),\n"
    "    texture_rotate: 0.f,\n"
    "    texture_scale: float2(1.f),\n"
    "    detail_texture_translate: float2(0.f),\n"
    "    detail_texture_rotate: 0.f,\n"
    "    detail_texture_scale: float2(1.f));\n";

  outfile.close();

    omniClientWait(omniClientCopy(fileName.c_str(),omniversePathMaterial.c_str(),nullptr, uploadCallback,eOmniClientCopy_Overwrite));


  TfToken materialNameToken(matName);
  // Make path for "/Root/Looks/Fieldstone";
  SdfPath matPath = SdfPath::AbsoluteRootPath()
      .AppendChild(_tokens->Root)
      .AppendChild(_tokens->Looks)
      .AppendChild(materialNameToken);
  UsdShadeMaterial newMat = UsdShadeMaterial::Define(g_stage, matPath);

  SdfAssetPath mdlShaderModule = SdfAssetPath("./files/materials/"+matName+".mdl");
  SdfPath shaderPath = matPath.AppendChild(materialNameToken);
  UsdShadeShader mdlShader = UsdShadeShader::Define(g_stage, shaderPath);
  mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));

  mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
  mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);

  UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
  mdlOutput.ConnectToSource(mdlShader, _tokens->out);
 

  shaderPath = matPath.AppendChild(_tokens->PrimST);
  UsdShadeShader primStShader = UsdShadeShader::Define(g_stage, shaderPath);
  primStShader.CreateIdAttr(VtValue(_tokens->PrimStShaderId));
  primStShader.CreateOutput(_tokens->result, SdfValueTypeNames->Float2);
  primStShader.CreateInput(_tokens->varname, SdfValueTypeNames->Token).Set(_tokens->st);
  
  //auto wTexture = material->getTexture("diffuse");

  if(!wTexture.expired()){
    auto texture = wTexture.lock();
    String omniversePathTexture =  "./files/materials/textures/"+texture->getPath().filename().string();

    std::string diffuseColorShaderName = matName + "DiffuseColorTex";
    std::string diffuseFilePath = omniversePathTexture;
    shaderPath = matPath.AppendChild(TfToken(diffuseColorShaderName));
    UsdShadeShader diffuseColorShader = UsdShadeShader::Define(g_stage, shaderPath);
    diffuseColorShader.CreateIdAttr(VtValue(_tokens->UsdUVTexture));
    UsdShadeInput texInput = diffuseColorShader.CreateInput(_tokens->file, SdfValueTypeNames->Asset);
    texInput.Set(SdfAssetPath(diffuseFilePath));
    texInput.GetAttr().SetColorSpace(_tokens->sRGB);
    diffuseColorShader.CreateInput(_tokens->st, SdfValueTypeNames->Float2).ConnectToSource(primStShader.CreateOutput(_tokens->result, SdfValueTypeNames->Float2));
    UsdShadeOutput diffuseColorShaderOutput = diffuseColorShader.CreateOutput(_tokens->rgb, SdfValueTypeNames->Float3);

    String usdPreviewSurfaceShaderName = matName + "PreviewSurface";
    shaderPath = matPath.AppendChild(TfToken(usdPreviewSurfaceShaderName));
    UsdShadeShader usdPreviewSurfaceShader = UsdShadeShader::Define(g_stage, shaderPath);
    usdPreviewSurfaceShader.CreateIdAttr(VtValue(_tokens->UsdPreviewSurface));
    UsdShadeInput diffuseColorInput = usdPreviewSurfaceShader.CreateInput(_tokens->diffuseColor, SdfValueTypeNames->Color3f);
    diffuseColorInput.ConnectToSource(diffuseColorShaderOutput);
    //UsdShadeInput normalInput = usdPreviewSurfaceShader.CreateInput(_tokens->normal, SdfValueTypeNames->Normal3f);
    //normalInput.ConnectToSource(normalShaderOutput);

    // Set the linkage between material and USD Preview surface shader
    UsdShadeOutput usdPreviewSurfaceOutput = newMat.CreateSurfaceOutput();
    auto result = usdPreviewSurfaceOutput.ConnectToSource(usdPreviewSurfaceShader, _tokens->surface);

  }
}

String 
Omniverse::addTexure(const Path& path)
{
  String omniversePathTexture =  "./textures/"+path.filename().string();
  uploadFileToOmniverse(path,omniversePathTexture);
  m_textures.push_back({path,omniversePathTexture,1});
  return omniversePathTexture;
}

void
Omniverse::uploadFileToOmniverse(const Path& path, const Path& omniversePath)
{
  omniClientWait(omniClientCopy(path.string().c_str(),omniversePath.string().c_str(),nullptr, uploadCallback,eOmniClientCopy_Overwrite));
}

void 
addMaterial(WPtr<Resourse> wMaterial,const UsdGeomMesh& UGmesh)
{
  if(wMaterial.expired()) return;
  auto material = cast<Material>(wMaterial.lock());
  
  auto matName = material->getName();
  auto wTexture = material->getTexture("diffuse");
  auto wNormal = material->getTexture("normalMap");
  String textureAttr  = "";
  String normalAttr  = "";

  if(!wTexture.expired()){
    String omniversePathTexture = Omniverse::instance().addTexure(wTexture.lock()->getPath());
    textureAttr = "\"" + omniversePathTexture + "\", ::tex::gamma_srgb";

  }

  if(!wNormal.expired()){
    String omniversePathTexture = Omniverse::instance().addTexure(wNormal.lock()->getPath()); 
    normalAttr = "\"" + omniversePathTexture + "\", ::tex::gamma_linear";
  }

  auto fileName = g_myPath+"materials/"+matName+".mdl";
  ofstream outfile (fileName);
  String omniversePathMaterial =   g_omniversePath + "/files/materials/"+matName+".mdl";
  outfile << "mdl 1.4;\n"
    "import ::OmniPBR::OmniPBR;\n"
    "import ::anno::author;\n"
    "import ::anno::description;\n"
    "import ::anno::display_name;\n"
    "import ::anno::key_words;\n"
    "import ::anno::version;\n"
    "import ::tex::gamma_mode;\n"
    "import ::state::normal;\n"
    "\n"
    "export material "<<matName<<"(*)\n"
    "[[\n"
    "    ::anno::display_name(\"Omni PBR \"),\n"
    "    ::anno::description(\"Omni PBR, supports ORM textures\"),\n"
    "    ::anno::version(1, 0, 0, \"\"),\n"
    "    ::anno::author(\"NVIDIA CORPORATION\"),\n"
    "    ::anno::key_words(string[](\"omni\", \"PBR\", \"omniverse\", \"generic\"))\n"
    "]]\n"
    " = ::OmniPBR::OmniPBR(\n"
    "    diffuse_color_constant: color(0.200000003f, 0.200000003f, 0.200000003f),\n"
    "    diffuse_texture: texture_2d("<<textureAttr<<"),\n"
    "    albedo_desaturation: 0.f,\n"
    "    albedo_add: 0.f,\n"
    "    albedo_brightness: 1.f,\n"
    "    diffuse_tint: color(1.f, 1.f, 1.f),\n"
    "    reflection_roughness_constant: 0.5f,\n"
    "    reflection_roughness_texture_influence: 1.f,\n"
    "    reflectionroughness_texture: texture_2d(),\n"
    "    metallic_constant: 0.f,\n"
    "    metallic_texture_influence: 1.f,\n"
    "    metallic_texture: texture_2d(),\n"
    "    specular_level: 0.5f,\n"
    "    enable_ORM_texture: true,\n"
    "    ORM_texture: texture_2d(),\n"
    "    ao_to_diffuse: 0.f,\n"
    "    ao_texture: texture_2d(),\n"
    "    enable_emission: false,\n"
    "    emissive_color: color(1.f, 0.100000001f, 0.100000001f),\n"
    "    emissive_mask_texture: texture_2d(),\n"
    "    emissive_intensity: 40.f,\n"
    "    bump_factor: 1.f,\n"
    "    normalmap_texture: texture_2d("<<normalAttr<<"),\n"
    "    detail_bump_factor: 0.300000012f,\n"
    "    detail_normalmap_texture: texture_2d(),\n"
    "    project_uvw: false,\n"
    "    world_or_object: false,\n"
    "    uv_space_index: 0,\n"
    "    texture_translate: float2(0.f),\n"
    "    texture_rotate: 0.f,\n"
    "    texture_scale: float2(1.f),\n"
    "    detail_texture_translate: float2(0.f),\n"
    "    detail_texture_rotate: 0.f,\n"
    "    detail_texture_scale: float2(1.f));\n";

  outfile.close();

  Omniverse::instance().uploadFileToOmniverse(fileName,omniversePathMaterial);


  //char* data = new char[256];
  //auto matName = material->getName();
  //auto fileName = g_myPath+"materials/"+matName+".mdl";
  //String omniversePathMaterial =   g_omniversePath + "/files/materials/"+matName+".mdl";

     // Create a material instance for this in USD
  TfToken materialNameToken(matName);
  // Make path for "/Root/Looks/Fieldstone";
  SdfPath matPath = SdfPath::AbsoluteRootPath()
      .AppendChild(_tokens->Root)
      .AppendChild(_tokens->Looks)
      .AppendChild(materialNameToken);
  UsdShadeMaterial newMat = UsdShadeMaterial::Define(g_stage, matPath);

  SdfAssetPath mdlShaderModule = SdfAssetPath("./files/materials/"+matName+".mdl");
  SdfPath shaderPath = matPath.AppendChild(materialNameToken);
  UsdShadeShader mdlShader = UsdShadeShader::Define(g_stage, shaderPath);
  mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));

  mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
  mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);

  UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
  mdlOutput.ConnectToSource(mdlShader, _tokens->out);
 

  shaderPath = matPath.AppendChild(_tokens->PrimST);
  UsdShadeShader primStShader = UsdShadeShader::Define(g_stage, shaderPath);
  primStShader.CreateIdAttr(VtValue(_tokens->PrimStShaderId));
  primStShader.CreateOutput(_tokens->result, SdfValueTypeNames->Float2);
  primStShader.CreateInput(_tokens->varname, SdfValueTypeNames->Token).Set(_tokens->st);
  
  wTexture = material->getTexture("diffuse");

  if(!wTexture.expired()){
    auto texture = wTexture.lock();
    String omniversePathTexture =  "./files/materials/textures/"+texture->getPath().filename().string();

    std::string diffuseColorShaderName = matName + "DiffuseColorTex";
    std::string diffuseFilePath = omniversePathTexture;
    shaderPath = matPath.AppendChild(TfToken(diffuseColorShaderName));
    UsdShadeShader diffuseColorShader = UsdShadeShader::Define(g_stage, shaderPath);
    diffuseColorShader.CreateIdAttr(VtValue(_tokens->UsdUVTexture));
    UsdShadeInput texInput = diffuseColorShader.CreateInput(_tokens->file, SdfValueTypeNames->Asset);
    texInput.Set(SdfAssetPath(diffuseFilePath));
    texInput.GetAttr().SetColorSpace(_tokens->sRGB);
    diffuseColorShader.CreateInput(_tokens->st, SdfValueTypeNames->Float2).ConnectToSource(primStShader.CreateOutput(_tokens->result, SdfValueTypeNames->Float2));
    UsdShadeOutput diffuseColorShaderOutput = diffuseColorShader.CreateOutput(_tokens->rgb, SdfValueTypeNames->Float3);

    String usdPreviewSurfaceShaderName = matName + "PreviewSurface";
    shaderPath = matPath.AppendChild(TfToken(usdPreviewSurfaceShaderName));
    UsdShadeShader usdPreviewSurfaceShader = UsdShadeShader::Define(g_stage, shaderPath);
    usdPreviewSurfaceShader.CreateIdAttr(VtValue(_tokens->UsdPreviewSurface));
    UsdShadeInput diffuseColorInput = usdPreviewSurfaceShader.CreateInput(_tokens->diffuseColor, SdfValueTypeNames->Color3f);
    diffuseColorInput.ConnectToSource(diffuseColorShaderOutput);
    //UsdShadeInput normalInput = usdPreviewSurfaceShader.CreateInput(_tokens->normal, SdfValueTypeNames->Normal3f);
    //normalInput.ConnectToSource(normalShaderOutput);

    // Set the linkage between material and USD Preview surface shader
    UsdShadeOutput usdPreviewSurfaceOutput = newMat.CreateSurfaceOutput();
    auto result = usdPreviewSurfaceOutput.ConnectToSource(usdPreviewSurfaceShader, _tokens->surface);

  }

  

  UsdShadeMaterialBindingAPI usdMaterialBinding(UGmesh);
  usdMaterialBinding.Bind(newMat);
  UsdShadeTokens->allPurpose;
}

void
addMesh(WPtr<Model> wModel,SdfPath parentPath, Transform transform)
{
  if(wModel.expired()) return;
  auto model = wModel.lock();
  auto modelName = model->getName();
    
  auto wMesh = model->getMesh();

  if(wMesh.expired()) return;

  auto mesh = wMesh.lock();

  SdfPath modelPrimPath = parentPath.AppendChild(TfToken(mesh->getName()));
  UsdGeomMesh UGmesh = UsdGeomMesh::Define(g_stage, modelPrimPath);
  if (!UGmesh){
    print("mesh not created");
    return;
  }
  
  UGmesh.CreateOrientationAttr(VtValue(UsdGeomTokens->rightHanded));
  
	VtArray<GfVec3f> points;
  VtArray<GfVec3f> meshNormals;
  auto vertices = mesh->getVertex();
  UsdGeomPrimvar attr2 = UGmesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
  VtVec2fArray valueArray;
  
	for (auto& vertex : vertices)
	{
		points.push_back(GfVec3f(vertex.location.x, vertex.location.y, vertex.location.z));
    meshNormals.push_back(GfVec3f(vertex.normal.x, vertex.normal.y, vertex.normal.z));
    valueArray.push_back(GfVec2f(vertex.textureCord.x,1.f-vertex.textureCord.y));
	}
	UGmesh.CreatePointsAttr(VtValue(points));
  UGmesh.CreateNormalsAttr(VtValue(meshNormals));
  
  auto translate = transform.getLocation();
  auto scale = transform.getScale();
  auto rotate = transform.getRotation();
  UGmesh.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(translate.x, translate.y, translate.z));
  UGmesh.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(scale.x, scale.y, scale.z));
	UGmesh.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(rotate.x,rotate.y,rotate.z));
  
  bool status = attr2.Set(valueArray);
  attr2.SetInterpolation(UsdGeomTokens->vertex);
  
  auto indices = mesh->getIndex();
  VtArray<int> vecIndices;
  for (auto& index : indices)
	{
		vecIndices.push_back(index);
	}
	UGmesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
  VtArray<int> faceVertexCounts;
	faceVertexCounts.resize(indices.size()/3); 
	fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
	UGmesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
  
  UsdPrim meshPrim = UGmesh.GetPrim();
	UsdAttribute displayColorAttr = UGmesh.CreateDisplayColorAttr();
	{
		VtVec3fArray valueArray;
		GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
		valueArray.push_back(rgbFace);
		displayColorAttr.Set(valueArray);
	}

  //addMaterial(model->getMaterial().lock(),UGmesh);


  //print("mesh created");
  auto wMat = model->getMaterial();
  addMaterial(model->getMaterial(),UGmesh);
  auto material = wMat.lock();
  material->m_onChanged.suscribe<Omniverse,&Omniverse::createMDL>(
    reinterpret_cast<Omniverse*>(Omniverse::instancePtr())
    );
  //m_meshes.push_back(makeSPtr)
  g_stage->Save();
  omniClientLiveProcess();
}

void 
addDirectionalLight(const DirectionalLight& light,SdfPath parentPath)
{
  auto lightPrimPath = parentPath.AppendChild(TfToken("directionalLight"));
  auto ULight = UsdLuxDistantLight::Define(g_stage, lightPrimPath);
  GfVec3f color(light.color.r,light.color.g,light.color.b);
  VtValue attr;
  ULight.CreateColorAttr(VtValue(color));
  float yaw = Math::atan(-light.direction.x/light.direction.y);
  float pitch = Math::atan(sqrt(light.direction.x*light.direction.x + light.direction.y*light.direction.y)/light.direction.z);
  ULight.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));
  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        xFormOp.Set(GfVec3f(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        xFormOp.Set(GfVec3d(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));
      }
    }
  }
  
}

void 
addPointLight(const PointLight& light,SdfPath parentPath)
{
  auto lightPrimPath = parentPath.AppendChild(TfToken("PointLight"));
  auto ULight = UsdLuxSphereLight::Define(g_stage, lightPrimPath);
  GfVec3f color(light.color.r,light.color.g,light.color.b);
  VtValue attr;
  ULight.CreateColorAttr(VtValue(color));
  ULight.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(light.location.x, light.location.y, light.location.z));
  ULight.CreateIntensityAttr(VtValue(light.intensity));

  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        xFormOp.Set(GfVec3f(light.location.x, light.location.y, light.location.z));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        xFormOp.Set(GfVec3d(light.location.x, light.location.y, light.location.z));
      }
    }
  }
}

void 
addSpotLight(const SpotLight& light,SdfPath parentPath)
{
  auto lightPrimPath = parentPath.AppendChild(TfToken("SpotLight"));
  auto ULight = UsdLuxDiskLight::Define(g_stage, lightPrimPath);
  GfVec3f color(light.color.r,light.color.g,light.color.b);
  VtValue attr;
  ULight.CreateColorAttr(VtValue(color));
  ULight.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(light.location.x, light.location.y, light.location.z));
  ULight.CreateIntensityAttr(VtValue(light.intensity));

  auto angle = ULight.GetPrim().GetAttribute(TfToken("shaping:cone:angle"));

  angle.Set(VtValue(light.angle));
  float yaw = Math::atan(-light.direction.x/light.direction.y);
  float pitch = Math::atan(sqrt(light.direction.x*light.direction.x + light.direction.y*light.direction.y)/light.direction.z);
  ULight.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));

  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = ULight.GetOrderedXformOps(&resetXformStack);
  for(auto& xFormOp: xFormOps){
    if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        xFormOp.Set(GfVec3f(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        xFormOp.Set(GfVec3d(yaw/Math::PI*180.f, pitch/Math::PI*180.f, 0));
      }
    }
    else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
      if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
        xFormOp.Set(GfVec3f(light.location.x, light.location.y, light.location.z));
      }
      else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
        xFormOp.Set(GfVec3d(light.location.x, light.location.y, light.location.z));
      }
    }
  }
}

void 
addActor(WPtr<Actor> wActor,SdfPath parentPath)
{
  if(wActor.expired()) return;
  auto actor = wActor.lock();
  auto actorName = actor->getName();
  //m_actors.push_back(wActor);
  SdfPath actorPrimPath = parentPath.AppendChild(TfToken(actorName));
  UsdGeomXform UGactor = UsdGeomXform::Define(g_stage, actorPrimPath);

  auto translate = actor->getGlobalLocation();
  auto scale = actor->getGlobalScale();
  auto rotate = actor->getGlobalRotation();
  UGactor.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(translate.x, translate.y, translate.z));
  UGactor.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(scale.x, scale.y, scale.z));
	UGactor.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(rotate.x,rotate.y,rotate.z));

  auto childs = actor->getChilds();
  for(auto& child : childs){
    addActor(child,actorPrimPath);
  }

  auto components = actor->getComponents<StaticMeshComponent>();

  for(auto& component : components){
    addMesh(cast<StaticMeshComponent>(component)->getModel(),actorPrimPath,cast<StaticMeshComponent>(component)->getTransform());

    //else if(component->getType() == COMPONENT_TYPE::k){
    //  addMesh(cast<StaticMeshComponent>(component)->getModel(),actorPrimPath,cast<StaticMeshComponent>(component)->getTransform());
    //}
  }

  auto directionalLights = actor->getComponents<DirectionalLightComponent>();
  for(auto& light : directionalLights){
    addDirectionalLight(cast<DirectionalLightComponent>(light)->m_light, actorPrimPath);
  }

  auto pointLights = actor->getComponents<PointLightComponent>();
  for(auto& light : pointLights){
    addPointLight(cast<PointLightComponent>(light)->m_light, actorPrimPath);
  }

  auto spotLights = actor->getComponents<SpotLightComponent>();
  for(auto& light : spotLights){
    addSpotLight(cast<SpotLightComponent>(light)->m_light, actorPrimPath);
  }
}

void 
Omniverse::addScene(WPtr<Actor> wActor)
{
  if(wActor.expired()) return;
  m_scene = wActor;
  SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
  UsdGeomXform rootPrim = UsdGeomXform::Define(g_stage, rootPrimPath);
  auto actor = wActor.lock();
  auto childs = actor->getChilds();
  for(auto& child : childs){
    addActor(child,rootPrimPath);
  }

}

void 
Omniverse::closeScene()
{
  g_stage = nullptr;
  m_scene = WPtr<Actor>();
}

void 
Omniverse::createSession(const String& name)
{
  g_liveSessionInfo.Initialize(m_stageUrl.c_str());
  g_liveSessionInfo.SetSessionName(name.c_str());
  auto liveSessionUrl = g_liveSessionInfo.GetLiveSessionUrl();
  print("LiveSessionUrl");
  print(liveSessionUrl);
  UsdStageRefPtr liveStage;
  liveStage = UsdStage::CreateNew(liveSessionUrl);
  SdfLayerHandle liveLayer = liveStage->GetRootLayer();
  g_stage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  g_stage->SetEditTarget(UsdEditTarget(liveLayer));
}

void 
Omniverse::joinToSession(const String& name)
{
  g_liveSessionInfo.Initialize(m_stageUrl.c_str());
  g_liveSessionInfo.SetSessionName(name.c_str());
  std::string liveSessionUrl = g_liveSessionInfo.GetLiveSessionUrl();
  UsdStageRefPtr liveStage;
  liveStage = UsdStage::Open(liveSessionUrl);
  SdfLayerHandle liveLayer = liveStage->GetRootLayer();
  g_stage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  g_stage->SetEditTarget(UsdEditTarget(liveLayer));
}

void 
Omniverse::leaveSession()
{
  g_stage->GetSessionLayer()->GetSubLayerPaths().clear();
  g_stage->SetEditTarget(UsdEditTarget(g_stage->GetRootLayer()));
}

void 
updateTransform(Transform& transform, Vector<UsdGeomXformOp>& xFormOps)
{
  if(transform.m_changed){
    for(auto& xFormOp: xFormOps){
      if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
        auto location = transform.getLocation();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(location.x, location.y, location.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(location.x, location.y, location.z));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
        auto myScale = transform.getScale();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(myScale.x, myScale.y, myScale.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(myScale.x, myScale.y, myScale.z));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
        auto myRot = transform.getRotation();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(myRot.x, myRot.y, myRot.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(myRot.x, myRot.y, myRot.z));
        }
      }
    }
  }

  else{
    for(auto& xFormOp: xFormOps){
      if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f position(0);
          xFormOp.Get(&position);
          transform.setLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d position(0);
          xFormOp.Get(&position);
          transform.setLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
        }
        
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f scale(0);
          xFormOp.Get(&scale);
          transform.setScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d scale(0);
          xFormOp.Get(&scale);
          transform.setScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f rotation(0);
          xFormOp.Get(&rotation);
          transform.setRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d rotation(0);
          xFormOp.Get(&rotation);
          transform.setRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
        }
      }
    }
  }
}

void
updateComponent(WPtr<StaticMeshComponent> wComponent, SdfPath parentPath)
{
  if(wComponent.expired()) return;
  auto component = cast<StaticMeshComponent>(wComponent.lock());

  auto wModel = component->getModel();

  if(wModel.expired()) return;

  auto model = wModel.lock();

  //auto modelName = model->getName();
  auto meshName = model->getMesh().lock()->getName();
  auto thisPath = parentPath.AppendChild(TfToken(meshName));

  auto modelPrimPath = parentPath.AppendChild(TfToken(meshName));
  auto UGmodel = UsdGeomMesh::Define(g_stage, modelPrimPath);

  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = UGmodel.GetOrderedXformOps(&resetXformStack);

  auto& transform = component->getTransform();

  updateTransform(component->getTransform(),xFormOps);
}



void
updateActor(WPtr<Actor> wActor, SdfPath parentPath)
{
  //return;
  if(wActor.expired()) return;
  auto actor = wActor.lock();

  auto actorName = actor->getName();
  auto thisPath = parentPath.AppendChild(TfToken(actorName));

  SdfPath actorPrimPath = parentPath.AppendChild(TfToken(actorName));
  UsdGeomXform UGactor = UsdGeomXform::Define(g_stage, actorPrimPath);
  SdfPathVector paths;
  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = UGactor.GetOrderedXformOps(&resetXformStack);
  
  updateTransform(actor->GetActorTransform(),xFormOps);
  
  auto childs = actor->getChilds();
  auto components = actor->getComponents<StaticMeshComponent>();
  
  auto usdChilds = UGactor.GetPrim().GetChildren();
	for (const auto& usdChild : usdChilds)
	{
    if (usdChild.IsA<UsdGeomMesh>())
		{
      bool existed = false;
      for(auto& component : components){
        auto wModel = cast<StaticMeshComponent>(component)->getModel();
        if(wModel.expired()) continue;
        auto model = wModel.lock();
        auto wMesh = model->getMesh();
        if(wMesh.expired()) return;
        auto mesh = wMesh.lock();
        auto meshName = mesh->getName();
        auto usdName = usdChild.GetName().GetString();
        if(meshName == usdName){
          updateComponent(cast<StaticMeshComponent>(component),UGactor.GetPath());
          existed = true;
          break;
        }
        
  
      }
      if(!existed){
        loadMeshFromUSD(UsdGeomMesh(usdChild),actor,usdChild.GetName());
      }
		}
    else if (usdChild.IsA<UsdGeomXform>())
		{
      bool existed = false;
      for(auto child : childs){
        if(child->getName() == usdChild.GetName().GetString()){
          updateActor(child,UGactor.GetPath());
          existed = true;
          break;
        }
      }
      if(!existed){
        loadActor(actor,usdChild);
      }
		}
	}
  
  for (auto child : childs )
	{
    bool existed = false;
    for(const auto& usdChild : usdChilds){
      if (usdChild.IsA<UsdGeomXform>())
		  {
        if(child->getName() == usdChild.GetName().GetString()){
          existed = true;
          break;
        }
		  }
    }
    if(!existed){
      addActor(child,UGactor.GetPath());
    }
	}
  for(auto& component : components)
	{
    auto wModel = cast<StaticMeshComponent>(component)->getModel();
    if(wModel.expired()) continue;
    auto model = wModel.lock();
    auto mesh = model->getMesh().lock();
    bool existed = false;
    for(const auto& usdChild : usdChilds){
      if (usdChild.IsA<UsdGeomMesh>())
		  {
        if(mesh->getName() == usdChild.GetName().GetString()){
          existed = true;
          break;
        }
		  }
    }
    if(!existed){
      addMesh(model,actorPrimPath,cast<StaticMeshComponent>(component)->getTransform());
    }
	}

  auto directionalLights = actor->getComponents<DirectionalLightComponent>();
  for(auto& light : directionalLights){
    addDirectionalLight(cast<DirectionalLightComponent>(light)->m_light, actorPrimPath);
  }

  auto pointLights = actor->getComponents<PointLightComponent>();
  for(auto& light : pointLights){
    addPointLight(cast<PointLightComponent>(light)->m_light, actorPrimPath);
  }

  auto spotLights = actor->getComponents<SpotLightComponent>();
  for(auto& light : spotLights){
    addSpotLight(cast<SpotLightComponent>(light)->m_light, actorPrimPath);
  }

  //for(auto child : childs){
  //  updateActor(child,thisPath);
  //}
  //auto components = actor->getComponents<StaticMeshComponent>();
  //
  //for(auto& component : components){
  //  updateComponent(cast<StaticMeshComponent>(component),UGactor.GetPath());
  //}
}

void 
Omniverse::update()
{

  omniClientLiveWaitForPendingUpdates();
  UsdGeomXformOp translateOp;
  GfVec3f position(0);
  GfVec3f scale(0);
  GfVec3f rotation(0);
  auto& resourceManager = ResoureManager::instance();

  if(m_scene.expired() || g_stage == nullptr) return;

  auto scene = m_scene.lock();

  auto childs = scene->getChilds();

  SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);

  UsdPrim root;

  auto range = g_stage->Traverse();
	for (const auto& node : range)
	{
		if (node.IsA<UsdGeomXform>())
		{
      root = node;
    }
    break;
	}

  auto usdChilds = root.GetChildren();
  
	for (const auto& usdChild : usdChilds)
	{
    if (usdChild.IsA<UsdGeomXform>())
		{
      bool existed = false;
      for(auto child : childs){
        if(child->getName() == usdChild.GetName().GetString()){
          updateActor(child,rootPrimPath);
          existed = true;
          break;
        }
      }
      if(!existed){
        loadActor(scene,usdChild);
      }
		}
	}

  for (auto child : childs )
	{
    bool existed = false;
    for(const auto& usdChild : usdChilds){
      if (usdChild.IsA<UsdGeomXform>())
		  {
        if(child->getName() == usdChild.GetName().GetString()){
          existed = true;
          break;
        }
		  }
      
    }
    if(!existed){
      addActor(child,root.GetPath());
    }
	}

  int texNum = 0;
  for(auto& texture : m_textures)
  {
    //size_t path = (size_t);
    omniClientWait(omniClientListCheckpoints(texture.omniverseDir.string().c_str(),&texNum, checkPointsCallBack));
    ++texNum;
  }
  
  //if(UsdChilds.end()-UsdChilds.begin()==)

  //for(auto child : childs){
  //  updateActor(child,rootPrimPath);
  //}

  g_stage->Save();
  omniClientLiveProcess();
}

}

