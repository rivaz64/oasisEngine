#pragma once
#include "oaComponent.h"

namespace oaEngineSDK
{

class CrowdComponent :
    public Component
{
public:

  void
  calcPoints();

  int m_numOfPoints;

  Vector2f m_minPoint;

  Vector2f m_maxPoint;

  float m_radii;

  int m_iterations;

  WPtr<SkeletalModel> m_model;

  Vector<Vector2f> m_points;
};

}


