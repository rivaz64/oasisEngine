#include "oaBaseApp.h"
#include "TestApp.h"
#include "oaGraphicAPI.h"
#include "oaLine.h"
using oaEngineSDK::BaseApp;
using oaEngineSDK::TestApp;

namespace oaEngineSDK{

void
analizeLine(const Plane& plane, const Vector3f& point1, const Vector3f& point2, Vector<Vector3f>& points){
  
  Vector3f intersection;
  if(Math::distance(plane,point1)*Math::distance(plane,point2) < 0.0f){
    Math::intersect(plane,Line(point1,point2),intersection);
    points.push_back(intersection);
  }
}

}

int main(){
  BaseApp* app = new TestApp;
  app->run();

  //oaEngineSDK::Plane plane(oaEngineSDK::Vector3f(1,0,0),oaEngineSDK::Vector3f(0,1,0),oaEngineSDK::Vector3f(0,0,1));
  //oaEngineSDK::Vector<oaEngineSDK::Vector3f> points;
  //
  //analizeLine(plane,oaEngineSDK::Vector3f(0,0,0),oaEngineSDK::Vector3f(1,2,3),points);
  
  delete app;

  app = 0;

  return 0;
}