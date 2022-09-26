#include "oaOmniverse.h"
#include <oaActor.h>
#include <oaGraphicsComponent.h>
#include <oaMesh.h>
#include <oaModel.h>
#include <oaResoureManager.h>
#include <oaActor.h>
#include <OmniClient.h>
//#include <OmniUsdLive.h>
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
#include <oaMaterial.h>
#include <oaTransform.h>
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
  auto stageUrl = m_destinationPath + "/" + name + ".live";//+(doLiveEdit ? ".live" : ".usd");
  
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
loadMeshFromUSD(UsdGeomMesh UGmesh, WPtr<Actor> wActor,const String& name)
{
  auto& resourceManager = ResoureManager::instance();
  auto actor = wActor.lock();
  auto gc = makeSPtr<GraphicsComponent>();
  auto model = makeSPtr<Model>();
  auto mesh = makeSPtr<StaticMesh>();
  auto newMaterial = resourceManager.m_defaultMaterial;
  resourceManager.registerResourse("m_"+name,model);
  //resourceManager.registerResourse("default material",cast<Resourse>(newMaterial));
  model->addMesh(mesh);
  model->addMaterial(newMaterial);
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
  UGmesh.GetFaceVertexCountsAttr().Get(&value);
  auto faceCount = value.Get<VtArray<int>>();

  SIZE_T numOfVertex = points.size();
  mesh->setVertexNum(numOfVertex);
  for(SIZE_T i=0; i<numOfVertex; ++i){
    mesh->setVertexAt(i,Vertex(
      Vector4f(points[i].data()[0],points[i].data()[1],points[i].data()[2],1.0f),
      Vector4f(normals[i].data()[0],normals[i].data()[1],normals[i].data()[2],0.0f),
      Vector2f(uvs[i].data()[0],uvs[i].data()[1])));
  }



  SIZE_T numOfIndices = indices.size();
  SIZE_T numOfFaces = faceCount.size();
  uint64 currectIndex = 0;
  //mesh->setIndexNum(numOfIndices);
  for(SIZE_T i=0; i<numOfFaces; ++i){
    mesh->m_index.push_back(indices[currectIndex]);
    mesh->m_index.push_back(indices[currectIndex+1]);
    mesh->m_index.push_back(indices[currectIndex+2]);
    
    if(faceCount[i] == 4){
      mesh->m_index.push_back(indices[currectIndex+2]);
      mesh->m_index.push_back(indices[currectIndex+3]);
      mesh->m_index.push_back(indices[currectIndex]);
      ++currectIndex;
    }
    currectIndex+=3;
  }

  mesh->writeBuffers();
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
  m_scene = wScene;
  auto scene = wScene.lock();
  auto stageUrl = m_destinationPath + "/" + name + ".live";
  g_stage = UsdStage::Open(stageUrl);
  if (!g_stage){
    print("Failure to connect to model in Omniverse");
    print(stageUrl.c_str());
    return;
  }
  else {
    print("connected to: " + stageUrl);
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
addMesh(WPtr<Model> wModel,SdfPath parentPath, Transform transform)
{
  if(wModel.expired()) return;
  auto model = wModel.lock();
  auto modelName = model->getName();
  //m_actors.push_back(wActor);
  SdfPath modelPrimPath = parentPath.AppendChild(TfToken(modelName));
  UsdGeomMesh UGmesh = UsdGeomMesh::Define(g_stage, modelPrimPath);
  auto mesh = model->getMesh(0).lock();
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
  
  g_stage->Save();
  omniClientLiveProcess();
  print("mesh created");
  //m_meshes.push_back(makeSPtr)
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

  auto components = actor->getComponents<GraphicsComponent>();

  for(auto& component : components){
    addMesh(cast<GraphicsComponent>(component)->getModel(),actorPrimPath,cast<GraphicsComponent>(component)->getTransform());
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
updateActor(WPtr<Actor> wActor, SdfPath parentPath)
{
  if(wActor.expired()) return;
  auto actor = wActor.lock();

  auto actorName = actor->getName();
  auto thisPath = parentPath.AppendChild(TfToken(actorName));

  SdfPath actorPrimPath = parentPath.AppendChild(TfToken(actorName));
  UsdGeomXform UGactor = UsdGeomXform::Define(g_stage, actorPrimPath);

  bool resetXformStack = false;
  Vector<UsdGeomXformOp> xFormOps = UGactor.GetOrderedXformOps(&resetXformStack);

  if(actor->hasChanged()){
    for(auto& xFormOp: xFormOps){
      if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
        auto location = actor->getLocalLocation();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(location.x, location.y, location.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(location.x, location.y, location.z));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
        auto myScale = actor->getLocalScale();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(myScale.x, myScale.y, myScale.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(myScale.x, myScale.y, myScale.z));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
        auto myRot = actor->getLocalRotation();
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          xFormOp.Set(GfVec3f(myRot.x, myRot.y, myRot.z));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          xFormOp.Set(GfVec3d(myRot.x, myRot.y, myRot.z));
        }
      }
    }
    g_stage->Save();
  }
  else{
    for(auto& xFormOp: xFormOps){
      if(xFormOp.GetOpType() == UsdGeomXformOp::TypeTranslate){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f position(0);
          xFormOp.Get(&position);
          actor->setActorLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d position(0);
          xFormOp.Get(&position);
          actor->setActorLocation(Vector3f(position.data()[0],position.data()[1],position.data()[2]));
        }
        
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeScale){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f scale(0);
          xFormOp.Get(&scale);
          actor->setActorScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d scale(0);
          xFormOp.Get(&scale);
          actor->setActorScale(Vector3f(scale.data()[0],scale.data()[1],scale.data()[2]));
        }
      }
      else if(xFormOp.GetOpType() == UsdGeomXformOp::TypeRotateXYZ){
        if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionFloat){
          GfVec3f rotation(0);
          xFormOp.Get(&rotation);
          actor->setActorRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
        }
        else if(xFormOp.GetPrecision() == UsdGeomXformOp::PrecisionDouble){
          GfVec3d rotation(0);
          xFormOp.Get(&rotation);
          actor->setActorRotation(Vector3f(rotation.data()[0],rotation.data()[1],rotation.data()[2]));
        }
      }
    }
  }
  
  auto childs = actor->getChilds();
  for(auto child : childs){
    updateActor(child,thisPath);
  }

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

  if(m_scene.expired()) return;

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

  //auto usdChilds = root.GetChildren();
	//for (const auto& usdChild : usdChilds)
	//{
  //  if (usdChild.IsA<UsdGeomXform>())
	//	{
  //    bool existed = false;
  //    for(auto child : childs){
  //      if(child->getName() == usdChild.GetName().GetString()){
  //        updateActor(child,rootPrimPath);
  //        existed = true;
  //        break;
  //      }
  //    }
  //    if(!existed){
  //      loadActor(scene,usdChild);
  //    }
	//		//print("Found UsdActor: " + child.GetName().GetString() );
  //    //loadActor(scene,child);
	//	}
	//}

  
  //if(UsdChilds.end()-UsdChilds.begin()==)

  for(auto child : childs){
    updateActor(child,rootPrimPath);
  }

  g_stage->Save();
  omniClientLiveProcess();
}

}

