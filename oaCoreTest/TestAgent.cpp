#include "TestAgent.h"

cwSDKtoolkit::Vector2f TestAgent::getWantedVelocity()
{
  if((m_pointToGo-m_position).len()<1){
    return {0.f,0.f};
  }
  return (m_pointToGo-m_position).normal();
}

