#include"oaVector3f.h"
#include "oaLine.h"
namespace oaEngineSDK {

Line::Line(Vector3f& A, Vector3f& B)
{
  startingPoint = A;
  Vector3f difference = B - A;
  direction = difference.normal();
  lenght = difference.len();
}

Vector3f Line::pointAt(float f)
{
  return startingPoint+direction*lenght*f;
}

float Line::distance(Vector3f& p)
{
  Vector3f u = p - startingPoint;
  return direction.cross(u).len();
}

}

