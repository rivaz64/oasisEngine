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
#include <pxr/usd/usdLux/domeLight.h>
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

namespace oaEngineSDK 
{

String g_myPath = "C:/Users/roriv/Documents/GitHub/oasisEngine/bin/omniverse/";

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
    String m_userFolder = "omniverse://localhost/Users";
    m_userName = getConnectedUsername();
    m_destinationPath = m_userFolder + "/" + m_userName;
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
      auto texturePath = StringUtilities::split(str,"\"")[1];
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
      material->setTexture("diffuse",texture);
      break;
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
uploadCallback(void* userData, OmniClientResult result)
{
}

void 
addMaterial(WPtr<Material> wMaterial,const UsdGeomMesh& UGmesh)
{
  if(wMaterial.expired()) return;
  auto material = wMaterial.lock();
  auto matName = material->getName();
  auto wTexture = material->getTexture("diffuse");
  if(wTexture.expired()) return;
  auto texture = wTexture.lock();
  auto fileName = g_myPath+"materials/"+matName+".mdl";
  ofstream outfile (fileName);
  String omniversePathTexture =   "omniverse://127.0.0.1/files/materials/textures/"+texture->getPath().filename().string();
  String omniversePathMaterial =   "omniverse://127.0.0.1/files/materials/"+matName+".mdl";
  outfile << "mdl 1.4;" << endl << 
    "using ::OmniPBR import OmniPBR;" << endl << 
    "import ::tex::gamma_mode;" << endl <<
    "import ::state::normal;" << endl <<
    "export material " << matName <<"(*)" << endl <<
    " = OmniPBR(" << endl <<
    "diffuse_texture: texture_2d(\"" << omniversePathTexture << "\", ::tex::gamma_srgb)"
    ");";
  outfile.close();
  char* data = new char[256];

  omniClientWait(omniClientCopy(texture->getPath().string().c_str(),omniversePathTexture.c_str(),nullptr, uploadCallback));
  omniClientWait(omniClientCopy(fileName.c_str(),omniversePathMaterial.c_str(),nullptr, uploadCallback));

     // Create a material instance for this in USD
  TfToken materialNameToken(matName);
  // Make path for "/Root/Looks/Fieldstone";
  SdfPath matPath = SdfPath::AbsoluteRootPath()
      .AppendChild(_tokens->Root)
      .AppendChild(_tokens->Looks)
      .AppendChild(materialNameToken);
  UsdShadeMaterial newMat = UsdShadeMaterial::Define(g_stage, matPath);

  SdfAssetPath mdlShaderModule = SdfAssetPath("./Materials/"+matName+".mdl");
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

  SdfPath modelPrimPath = parentPath.AppendChild(TfToken(model->getName()));
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
    valueArray.push_back(GfVec2f(vertex.textureCord.x,vertex.textureCord.y));
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

  addMaterial(model->getMaterial().lock(),UGmesh);
  //}
  
  
  print("mesh created");
  addMaterial(model->getMaterial(),UGmesh);
  //m_meshes.push_back(makeSPtr)
  g_stage->Save();
  omniClientLiveProcess();
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

  auto modelName = model->getName();
  auto thisPath = parentPath.AppendChild(TfToken(modelName));

  auto modelPrimPath = parentPath.AppendChild(TfToken(modelName));
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
        if(model->getName() == usdChild.GetName().GetString()){
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
    bool existed = false;
    for(const auto& usdChild : usdChilds){
      if (usdChild.IsA<UsdGeomMesh>())
		  {
        if(model->getName() == usdChild.GetName().GetString()){
          existed = true;
          break;
        }
		  }
    }
    if(!existed){
      addMesh(model,actorPrimPath,cast<StaticMeshComponent>(component)->getTransform());
    }
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

  
  //if(UsdChilds.end()-UsdChilds.begin()==)

  //for(auto child : childs){
  //  updateActor(child,rootPrimPath);
  //}

  g_stage->Save();
  omniClientLiveProcess();
}

}

