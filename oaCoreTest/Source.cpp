#include "oaBaseApp.h"

using oaEngineSDK::BaseApp;

int main(){
  BaseApp::startUp();
  BaseApp::instancePtr()->run();
  BaseApp::shutDown();
  return 0;
}