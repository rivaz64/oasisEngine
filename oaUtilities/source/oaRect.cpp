#include "oaRect.h"

oaEngineSDK::Rect::Rect(const Vector2f& A, const Vector2f& B)
{
  minPoint = { Math::min(A.x,B.x),Math::min(A.y,B.y) };
  maxPoint = { Math::max(A.x,B.x),Math::max(A.y,B.y) };
}

bool oaEngineSDK::Rect::isPointInside(const Vector2f& point)
{
  return point.x>minPoint.x && point.x < maxPoint.x &&
    point.y>minPoint.y && point.y < maxPoint.y;
}
