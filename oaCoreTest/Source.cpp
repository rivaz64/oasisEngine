#include "oaBaseApp.h"
#include "TestApp.h"
#include "oaStringUtilities.h"

using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;

int main(){
  //BaseApp* app = new TestApp;
  //app->run();

  auto splited = oaEngineSDK::StringUtilities::split("hello world"," ");
  
  //delete app;

  //app = 0;

  return 0;
}