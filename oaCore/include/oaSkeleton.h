/**
* @file oaSkeleton.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

struct ModelComponent;

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
class OA_CORE_EXPORT Skeleton
{
 public:

  /**
   * @brief all the nodes of the skeleton
  */
  SPtr<SkeletalNode> m_skeleton;

  /**
   * @brief the final matrizes 
  */
  Map<String,Matrix4f> m_finalMatrix;

  /**
   * @brief the mapping for the names of the bones
  */
  Map<String,Matrix4f> m_boneMaping;

  /**
   * @brief the inverse of the root
  */
  Matrix4f m_globalInverse;

  String m_name;
};

}
