#include "oaOmniverse.h"
#include <oaActor.h>
#include <oaGraphicsComponent.h>
#include <oaMesh.h>
#include <oaModel.h>
#include <oaResoureManager.h>
#include <oaActor.h>
#include <OmniClient.h>
#include <OmniUsdLive.h>
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/mesh.h"
#include "pxr/usd/usdGeom/metrics.h"
#include <pxr/base/gf/matrix4f.h>
#include "pxr/base/gf/vec2f.h"
#include "pxr/usd/usdUtils/pipeline.h"
#include "pxr/usd/usdUtils/sparseValueWriter.h"
#include "pxr/usd/usdShade/material.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/usd/usdGeom/primvar.h"
#include "pxr/usd/usdShade/input.h"
#include "pxr/usd/usdShade/output.h"
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/cube.h>
#include "pxr/usd/usdShade/materialBindingAPI.h"
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>
#include <oaActor.h>
#include <oaGraphicsComponent.h>
#include <oaModel.h>
#include <oaMesh.h>
#include <oaResoureManager.h>
namespace oaEngineSDK 
{

PXR_NAMESPACE_USING_DIRECTIVE

TF_DEFINE_PRIVATE_TOKENS(
	_tokens,
	(Root)
  (st)
  (DistantLight)
);

using std::fill;

void SetOp(UsdGeomXformable& xForm, UsdGeomXformOp& op, UsdGeomXformOp::Type opType, const GfVec3d& value, const UsdGeomXformOp::Precision precision)
{
	//if (!op)
	//{
	//	op = xForm.AddXformOp(opType, precision);
	//	cout << " Adding " << UsdGeomXformOp::GetOpTypeToken(opType) << endl;
	//}

	//if (op.GetPrecision() == UsdGeomXformOp::Precision::PrecisionFloat)
		//op.Set(GfVec3d(value));
	//else
  op.Set(value);

	cout << " Setting " << UsdGeomXformOp::GetOpTypeToken(opType) << endl;
}

//static void OmniClientConnectionStatusCallbackImpl(void* userData, const char* url, OmniClientConnectionStatus status) noexcept
//{
//    // Let's just print this regardless
//    {
//        
//        std::cout << "Connection Status: " << omniClientGetConnectionStatusString(status) << " [" << url << "]" << std::endl;
//    }
//    if (status == eOmniClientConnectionStatus_ConnectError)
//    {
//        // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
//        std::cout << "[ERROR] Failed connection, exiting." << std::endl;
//        exit(-1);
//    }
//}
//
PXR_NAMESPACE_USING_DIRECTIVE
UsdStageRefPtr g_stage;

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
  omniUsdLiveWaitForPendingUpdates();

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
Omniverse::createModel(const String& name)
{
  auto stageUrl = m_destinationPath + "/" + name + ".usd";//+(doLiveEdit ? ".live" : ".usd");
  
  print("Waiting for " + stageUrl + " to delete... ");
  omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
  print("finished");
  
  g_stage = UsdStage::CreateNew(stageUrl);
  if (!g_stage){
      print("Failure to create model in Omniverse");
      print(stageUrl.c_str());
      return;
  }
  else {
      print("New stage created: " + stageUrl);
  }

  
  
}

void
loadMeshFromUSD(UsdGeomMesh UGmesh, WPtr<Actor> wActor)
{
  auto& resourceManager = ResoureManager::instance();
  auto actor = wActor.lock();
  auto gc = makeSPtr<GraphicsComponent>();
  auto model = makeSPtr<Model>();
  auto mesh = makeSPtr<StaticMesh>();
  resourceManager.registerResourse("usd model",model);
  model->addMesh(mesh);
  model->addMaterial(resourceManager.m_defaultMaterial);
  gc->setModel(model);
  actor->attachComponent(gc);
  VtValue value;
  UGmesh.GetPointsAttr().Get(&value);
  auto points = value.Get<VtArray<GfVec3f>>();
  UGmesh.GetNormalsAttr().Get(&value);
  auto normals = value.Get<VtArray<GfVec3f>>();
  UGmesh.GetPrimvar(_tokens->st).GetAttr().Get(&value);
  auto uvs = value.Get<VtVec2fArray>();
  UGmesh.GetFaceVertexIndicesAttr().Get(&value);
  auto indices = value.Get<VtArray<int>>();

  SIZE_T numOfVertex = points.size();
  mesh->setVertexNum(numOfVertex);
  for(SIZE_T i=0; i<numOfVertex; ++i){
    mesh->setVertexAt(i,Vertex(
      Vector4f(points[i].data()[0],points[i].data()[1],points[i].data()[2],1.0f),
      Vector4f(normals[i].data()[0],normals[i].data()[1],normals[i].data()[2],0.0f),
      Vector2f(uvs[i].data()[0],uvs[i].data()[1])));
  }

  SIZE_T numOfIndices = indices.size();
  mesh->setIndexNum(numOfIndices);
  for(SIZE_T i=0; i<numOfIndices; ++i){
    mesh->setIndexAt(i,indices[i]);
  }

  mesh->writeBuffers();
}

void 
Omniverse::connectToModel(const String& name, WPtr<Actor> wScene)
{
  auto scene = wScene.lock();
  auto stageUrl = m_destinationPath + "/" + name + ".usd";
  g_stage = UsdStage::Open(stageUrl);
  if (!g_stage){
    print("Failure to connect to model in Omniverse");
    print(stageUrl.c_str());
    return;
  }
  else {
    print("connected to: " + stageUrl);
  }

  auto range = g_stage->Traverse();
	for (const auto& node : range)
	{
		if (node.IsA<UsdGeomMesh>())
		{
			{
				std::cout << "Found UsdGeomMesh: " << node.GetName() << std::endl;
			}
      auto newActor = makeSPtr<Actor>();
      scene->attach(newActor);
      newActor->setName(node.GetName());
			loadMeshFromUSD(UsdGeomMesh(node),newActor);
		}
	}

}

void 
Omniverse::addActor(WPtr<Actor> wActor)
{
  if(wActor.expired()) return;
  auto actor = wActor.lock();
  auto actorName = actor->getName();
  m_actors.push_back(wActor);
  SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
  UsdGeomXform rootPrim = UsdGeomXform::Define(g_stage, rootPrimPath);
  SdfPath meshPrimPath = rootPrimPath.AppendChild(TfToken(actorName));
  UsdGeomMesh UGmesh = UsdGeomMesh::Define(g_stage, meshPrimPath);
  auto mesh = actor->getComponent<GraphicsComponent>().lock()->getModel().lock()->getMesh(0).lock();
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

  UGmesh.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(0.0f, 0.0f, 0.0f));
  UGmesh.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(1.0f, 1.0f, 1.0f));
	UGmesh.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3d(0.0, 0.0, 0.0));

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

  g_stage->Save();
  omniUsdLiveProcess();
  //m_meshes.push_back(makeSPtr)
}

void 
Omniverse::update()
{
  omniUsdLiveWaitForPendingUpdates();
  UsdGeomXformOp translateOp;
  GfVec3f position(0);
  GfVec3f scale(0);
  GfVec3f rotation(0);
  auto& resourceManager = ResoureManager::instance();
  for(auto& wActor : m_actors){
    auto actor = wActor.lock();
    auto actorName = actor->getName();
    SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
    UsdGeomXform rootPrim = UsdGeomXform::Define(g_stage, rootPrimPath);
    SdfPath meshPrimPath = rootPrimPath.AppendChild(TfToken(actorName));
    UsdGeomMesh UGmesh = UsdGeomMesh::Define(g_stage, meshPrimPath);
    UsdGeomXformable xForm = UGmesh;
    bool resetXformStack = false;
    Vector<UsdGeomXformOp> xFormOps = xForm.GetOrderedXformOps(&resetXformStack);
    for(auto& xFormOp: xFormOps){
      if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
        auto location = actor->getGlobalLocation();
        xFormOp.Get(&position);
        xFormOp.Set(GfVec3f(location.x, location.y, location.z));
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
        auto myScale = actor->getGlobalScale();
        xFormOp.Get(&scale);
        xFormOp.Set(GfVec3f(myScale.x, myScale.y, myScale.z));
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
        auto myRot = actor->getGlobalRotation();
        xFormOp.Get(&rotation);
        xFormOp.Set(GfVec3f(myRot.x, myRot.y, myRot.z));
      }
    }
    
    //SetOp(xForm, translateOp, UsdGeomXformOp::TypeTranslate, position, UsdGeomXformOp::Precision::PrecisionFloat);
    //std::vector<UsdGeomXformOp> xFormOpsReordered;
	  //xFormOpsReordered.push_back(translateOp);
    //xForm.SetXformOpOrder(xFormOpsReordered);
    //g_stage->Save();
    auto pos = rotation.GetArray();
    print(StringUtilities::floatToString(float(pos[0]))+" "+StringUtilities::floatToString(float(pos[1]))+" "+StringUtilities::floatToString(float(pos[2])));
    g_stage->Save();
  }
  
}

}

