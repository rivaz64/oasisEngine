#include <oaOmniverse.h>
#include <oaPlugInManager.h>

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


PXR_NAMESPACE_USING_DIRECTIVE

#ifdef OA_PY_EXPORTS
#define OA_PY_EXPORT __declspec(dllexport)
#else
#define OA_PY_EXPORT __declspec(dllimport)
#endif
using oaEngineSDK::OmniverseApi;
using oaEngineSDK::Omniverse;
using oaEngineSDK::WPtr;
using oaEngineSDK::Texture;
using oaEngineSDK::print;
using oaEngineSDK::String;
using oaEngineSDK::Vector;
using oaEngineSDK::PlugInManager;
using oaEngineSDK::StringUtilities;

extern "C"
{

  String
  getConnectedUsername(String userFolder)
  {
    std::string userName = "_none_";
    omniClientWait(omniClientGetServerInfo(userFolder.c_str(), &userName, [](void* userData, OmniClientResult result, struct OmniClientServerInfo const * info) noexcept
    {
      std::string* userName = static_cast<std::string*>(userData);
      if (userData && userName && info && info->username)
      {
          userName->assign(info->username);
      }
    }));
    return userName;
  }

  static void logCallback(const char* threadName, const char* component, OmniClientLogLevel level, const char* message) noexcept
  {
    std::ofstream file;
    file.open("C:/Users/roriv/Documents/kritadas/output.txt",std::ios::out | std::ios::app);
    file<<message<<std::endl;
    file.close();
    //print(message);
  }


  OA_PY_EXPORT void
  pyOmniverseStart()
  {
    omniClientSetLogCallback(logCallback);
  
    if (!omniClientInitialize(kOmniClientVersion)){
      print("omniverse not working");
      return;
    }

    //print("omniverse working");
    //PlugInManager::startUp();
    //OmniverseApi::startUp<Omniverse>();
    //Omniverse::startUp();
    //PlugInManager::instance().load("E:/github/oasisEngine/bin/x64/oaOmniversed.dll");
  }

  OA_PY_EXPORT void
  pyOmniverseShutDown()
  {
    //Omniverse::shutDown();
  }

  OA_PY_EXPORT void
  pyConnect()
  {
    String destinationPath;
    if (destinationPath == "")
    {
      //m_userFolder = "omniverse://192.168.138.220/Users";
      auto g_userFolder = "omniverse://localhost/Users";
      auto g_userName = getConnectedUsername(g_userFolder);
      print("user : " + g_userName);
      //auto g_omniversePath = /*m_destinationPath =*/ g_userFolder + "/" + g_userName;
    }
  }

  void
  uploadCallback(void* userData, OmniClientResult result)
  {
    print(StringUtilities::intToString(result));
  }

  OA_PY_EXPORT void
  pyUploadFileToOmniverse(char* path, char* omniversePath)
  {
    omniClientWait(omniClientCopy(path,omniversePath,nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }

  OA_PY_EXPORT void
  pyDownloadFileFromOmniverse(char* omniversePath , char* path)
  {
    omniClientWait(omniClientCopy(omniversePath,path,nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }

  OA_PY_EXPORT void
  pyDeleteOmniverseFile(char* omniversePath)
  {
    omniClientWait(omniClientDelete(omniversePath,nullptr, uploadCallback));
  }

  bool waiting = false;
  uint32_t numOfCheckpoints;

  void checkPointsCallBack(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
  {
    for(auto i = 0; i<((int)numEntries)-2; i++){
      std::string path = reinterpret_cast<char*>(userData);
      path += "?checkpoint=";
      auto entry = entries[i].relativePath;
      for (int j = 1; entry[j] != '\0'; ++j)
      {
        path += entry[j];
        omniClientWait(omniClientDelete(path.c_str(),nullptr, uploadCallback));
      }
    }
  }

  OA_PY_EXPORT void
  pyDeleteCheckPoints(char* omniversePath)
  {
    waiting = true;
    omniClientWait(omniClientListCheckpoints(omniversePath,omniversePath, checkPointsCallBack));
  }
   

  OA_PY_EXPORT void
  test()
  {
    omniClientWait(omniClientCopy("E:/github/oasisEngine/bin/textures/wall.jpg","omniverse://127.0.0.1/Users/rivaz/files/materials/textures/wall.jpg",nullptr, uploadCallback,eOmniClientCopy_Overwrite));
  }

  void
  checkNode(const UsdPrim& node,std::vector<String>& textures)
  {
    if(false){//node.IsA<UsdShadeMaterial>()){
      //auto& material = node.As<UsdShadeMaterial>();
      auto shaders = node.GetPrim().GetChildren();
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

        for(int i = 0; i< dif; ++i){
          dotPath+=resolvedPath[i];
        }

        for(int i = 2; i< dif; ++i){
          if(assetPath[i]=='/') break;
          dotPath+=assetPath[i];
        }
        textures.push_back("matPath->"+String(p.GetResolvedPath().c_str()));
      }
    }
    else{
      auto usdChilds = node.GetChildren();
  
	    for (const auto& usdChild : usdChilds)
      {
        checkNode(usdChild,textures);
      }
    }
  }

  OA_PY_EXPORT void*
  pyOpenScene(char* m_stageUrl)
  {
    auto stage = UsdStage::CreateNew(m_stageUrl);//UsdStage::Open(m_stageUrl);
    //stage->
    //auto range = stage->Traverse();
    std::vector<String> textures;
    std::ofstream file;
    file.open("C:/Users/roriv/Documents/kritadas/output.txt",std::ios::out | std::ios::app);
    if (!stage){
      file<<"Failure to create to model in Omniverse"<<std::endl;
      file<<m_stageUrl<<std::endl;
    }
    file.close();
	  //for (const auto& node : range)
	  //{
    //  file<<node.GetName().GetString()<<std::endl;
	  //	//checkNode(node,textures);
	  //}
    //auto root = stage->GetDefaultPrim();
    
    
    
    //for(auto& texture : textures){
    //  file<<texture<<std::endl;
    //}
    
    stage.Reset();
    return nullptr;
    //auto scene = UsdStage::Open(m_stageUrl);
  }
}