/**
* @file oaSkeleton.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
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

  /**
   * @brief the childs of this node
  */
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

  /**
   * @brief the final matrizes 
  */
  //Vector<Matrix4f> finalMatrix;

  /**
   * @brief the mapping for the names of the bones
  */
  Map<String,Matrix4f> boneMaping;

  /**
   * @brief the inverse of the root
  */
  Matrix4f globalInverse;
};

}
