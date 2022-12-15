#pragma once
#include <Agent.h>
#include <Vector2f.h>
class TestAgent :
  public cwSDKtoolkit::Agent
{
public:

  TestAgent(const cwSDKtoolkit::Vector2f& position, const cwSDKtoolkit::Vector2f& pointToGo): 
    m_pointToGo(pointToGo), cwSDKtoolkit::Agent(15.f,3,2,12,50,position) 
  {
    m_velocity = {0.0f,0.0f};
  }

  cwSDKtoolkit::Vector2f getWantedVelocity() override;

  cwSDKtoolkit::Vector2f m_pointToGo;
};

