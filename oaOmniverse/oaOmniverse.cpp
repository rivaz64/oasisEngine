#include "oaOmniverse.h"
#include <OmniClient.h>

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
static void logCallback(const char* threadName, const char* component, OmniClientLogLevel level, const char* message) noexcept
{
    print(message);
}

void 
Omniverse::onStartUp()
{
  omniClientSetLogCallback(logCallback);
  
  if (!omniClientInitialize(kOmniClientVersion)){
     return;
  }
}

void 
Omniverse::onShutDown()
{
  // Calling this prior to shutdown ensures that all pending live updates complete.
    omniClientLiveWaitForPendingUpdates();

    // The stage is a sophisticated object that needs to be destroyed properly.  
    // Since gStage is a smart pointer we can just reset it
    //gStage.Reset();

    //omniClientTick(1000);
    omniClientShutdown();
}

}

