#include "WanderAgent.h"

Vector2f WanderAgent::getWantedVelocity()
{
  if((m_pointToGo-m_position).lenSqrd()<m_wanderAcceptanceRadius*m_wanderAcceptanceRadius){
    //m_actualTime-=m_wanderTime;
    float angle = (static_cast<float>(rand())/static_cast<float>(RAND_MAX))*3.14159265358979323846f*2.f;
    m_pointToGo = m_position+m_velocity.normal()*m_wanderOfset+Vector2f(cos(angle),sin(angle))*m_wanderRadius;
    auto delta = m_pointToGo;
    delta = delta/2.f;
    m_pointToGo = m_pointToGo-delta;
  }
  return (m_pointToGo-m_position).normal();
}
