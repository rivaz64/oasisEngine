#include <Agent.h>
using namespace cwSDKtoolkit;
class WanderAgent :
  public Agent
{
public:
  static Vector<Vector2f> velocities;
  WanderAgent(const Vector2f& position, const Vector2f& pointToGo): 
    m_pointToGo(pointToGo), Agent(15.f,1.5,2,12,50,position) 
  {
    float velAngle = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
    m_velocity = {cos(velAngle),sin(velAngle)};
  }

  Vector2f getWantedVelocity() override;

  Vector2f m_pointToGo;

  float m_wanderAcceptanceRadius=18.f;

  float m_wanderOfset=72.f;

  float m_wanderRadius = 36.f;
};
