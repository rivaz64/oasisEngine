#include "oaSimplexNoise.h"
#include "oaVector3I.h"
#include "oaVector3f.h"
#include "oaRandom.h"

namespace oaEngineSDK{

float SQRT3 = Math::sqrt(3.f);
float F2 = .5f * (SQRT3 - 1.f);
float G2 = (3.f - SQRT3) / 6.f;

float 
SimplexNoise::valueAt(const Vector2f& point)
{
  float s = (point.x+point.y)*F2;
  Vector2f ij = (point+s).floor();
  float t = (ij.x+ij.y)*G2;
  //corner 1
  Vector2f c1 = ij-t;
  //ofset1
  Vector2f o1 = point-c1;

  Vector2f offset;
  if(o1.x>o1.y) {
    offset.x=1; 
    offset.y=0;
  } 
  else {
    offset.x=0; 
    offset.y=1;
  }
  
  Vector2f ij2=ij+offset;

  Vector2f ij3 = ij + Math::sqrt(2);

  Vector2f g2 = Random::vector2(ij2);

  Vector2f g3 = Random::vector2(ij3);

  Vector2f o2 = o1-offset+G2;

  Vector2f o3 = o1 - 1.f + 2.f * G2;

  Vector2f c2 = point-o2;

  Vector2f c3 = point-o3;

  Vector2f rv1 = Random::vector2(c1);
  Vector2f rv2 = Random::vector2(c2);
  Vector2f rv3 = Random::vector2(c3);

  return 70.f*(calculateGradient(rv1,o1)
              +calculateGradient(rv2,o2)
              +calculateGradient(rv3,o3));
}


float
SimplexNoise::calculateGradient(const Vector2f& gradient, const Vector2f& offset)
{
  float t = .5f-offset.magnitud();
  if(t<0){
    return 0;
  }
  else{
    t*=t;
    return t*t*Vector2f::dot(gradient,offset);
  }
}

}

