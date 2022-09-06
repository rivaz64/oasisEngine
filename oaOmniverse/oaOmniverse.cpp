#include "oaOmniverse.h"
#include <OmniClient.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#endif
#include <mutex>
#include <memory>
#include <map>
#include <condition_variable>
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
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>
#include <pxr/usd/usd/common.h>

namespace oaEngineSDK 
{

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

}

