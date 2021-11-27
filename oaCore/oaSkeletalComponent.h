/**
* @file oaSkeletalComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaComponent.h"
#include "oaTree.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

/**
 * @brief the component for the skeleton
*/
class SkeletalComponent :
  public Component
{
  Tree<Matrix4f> skeleton;
};

}


