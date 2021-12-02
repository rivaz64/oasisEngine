/**
* @file oaAnimation.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/1/2021
*/

#include "oaAnimation.h"

namespace oaEngineSDK{

void 
Animation::update(float deltaTime)
{
  float timeInTicks = ticksPerSecond * deltaTime;

  float animationTime =  Math::modf(timeInTicks,duration);


}

void 
Animation::readNodeHeirarchy(float animationTime,const AnimNode& node, const Matrix4f& transform)
{
  
}

}

