#include "oaBaseApp.h"
#include "TestApp.h"
#include "oaRandom.h"

using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;

int main(){
  //srand(time(NULL));
  BaseApp::startUp<TestApp>();
  BaseApp::instancePtr()->run();
  BaseApp::shutDown();
  return 0;
}