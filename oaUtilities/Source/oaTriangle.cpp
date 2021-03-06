#include "oaTriangle.h"
#include "oaLine.h"

namespace oaEngineSDK{

Vertex
interpolateVertex(const Vertex& v1,const Vertex& v2, float w){
  Vertex vertex;
  vertex.location = Vector4f::interpolate(v1.location,v2.location,w);
  vertex.textureCord = Vector2f::interpolate(v1.textureCord,v2.textureCord,w);
  vertex.normal = Vector4f::interpolate(v1.normal,v2.normal,w);
  vertex.tangent = Vector4f(7,7,7,7);//Vector4f::interpolate(v1.tangent,v2.tangent,w);
  vertex.bitangent = Vector4f(7,7,7,7);//Vector4f::interpolate(v1.bitangent,v2.bitangent,w);
  return vertex;
}

bool
analizeLine(const Plane& plane, const Vertex& point1, const Vertex& point2, Vector<Vertex>& points){
  
  Vector3f intersection;
  if(Math::distance(plane,point1.location.xyz)*Math::distance(plane,point2.location.xyz) < 0.0f){
    Math::intersect(plane,Line(point1.location.xyz,point2.location.xyz),intersection);
    auto w = Vector3f::getInterpolation(point1.location.xyz,point2.location.xyz,intersection);
    auto inter = interpolateVertex(point1,point2,w);
    //inter.location = Vector4f(intersection,0);
    points.push_back(inter);
    //points.push_back(intersection);
    return  true;
  }
  return false;
}

bool 
Triangle::separate(const Plane& plane,
           Vector<Vertex>& points, 
           Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide,
           bool& isTriFront)
{
  Vector<int32> index;
 
  int32 otherside;
  
  float dist1 = Math::distance(plane,m_point1.location.xyz);
  float dist2 = Math::distance(plane,m_point2.location.xyz);
  float dist3 = Math::distance(plane,m_point3.location.xyz);
  isTriFront = dist1>0;
  Vector<bool> isFront;

  if(analizeLine(plane,m_point1,m_point2,points)){
    isFront.push_back(dist2>0);
    isFront.push_back(dist3>0);
    isFront.push_back(dist1>0);
    index.push_back(1);
    if(analizeLine(plane,m_point2,m_point3,points)){
      index.push_back(4);
      index.push_back(2);
      otherside = 1;
    }
    else if(analizeLine(plane,m_point3,m_point1,points)){
      index.push_back(2);
      index.push_back(4);
      otherside = 0;
    }
    else{
      return false;
    }
    index.push_back(0);
  }
  else if(analizeLine(plane,m_point2,m_point3,points) && analizeLine(plane,m_point3,m_point1,points)){
    isFront.push_back(dist3>0);
    isFront.push_back(dist1>0);
    isFront.push_back(dist2>0);
    index.push_back(2);
    index.push_back(4);
    index.push_back(0);
    index.push_back(1);
    otherside = 2;
  }
  else{
    return false;
  }

  for(int32 i=0;i<3;i++){
    if(isFront[i]){
      finalIndexPositiveSide.push_back(3);
      finalIndexPositiveSide.push_back(index[i]);
      finalIndexPositiveSide.push_back(index[i+1]);
    }
    else{
      finalIndexNegativeSide.push_back(3);
      finalIndexNegativeSide.push_back(index[i]);
      finalIndexNegativeSide.push_back(index[i+1]);
    }
    
  }
  return true;
}


}
