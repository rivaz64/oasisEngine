#include "oaBaseApp.h"
#include "TestApp.h"
#include "oaRandom.h"

using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;

int main(){
  //srand(time(NULL));
  BaseApp* app = new TestApp;
  //app.startUp<TestApp>();
  app->run();
  //app.shutDown();

  delete app;

  app = 0;

  return 0;
}