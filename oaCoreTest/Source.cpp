#include "oaBaseApp.h"
#include "TestApp.h"
using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;
int main(){
  BaseApp::startUp<TestApp>();
  BaseApp::instancePtr()->run();
  BaseApp::shutDown();
  return 0;
}