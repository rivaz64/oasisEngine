#include "oaBaseApp.h"
#include "TestApp.h"
using oaEngineSDK::BaseApp;

int main(){
  BaseApp::startUp<TestApp>();
  BaseApp::instancePtr()->run();
  BaseApp::shutDown();
  return 0;
}