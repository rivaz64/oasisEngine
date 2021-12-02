/**
* @file oaSkeleton.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaTree.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

/**
 * @brief a node of a skeleton
*/
struct SkeletalNode{
  
  /**
   * @brief the name of this node
  */
  String name;
  /**
   * @brief the transform of this node
  */
  Matrix4f transform;

  Vector<SPtr<SkeletalNode>> childs;
};

/**
 * @brief the skeleton for the animations
*/
class Skeleton
{
 public:
  
  /**
   * @brief all the nodes of the skeleton
  */
  SPtr<SkeletalNode> skeleton;

  Matrix4f globalInverse;
};

}
