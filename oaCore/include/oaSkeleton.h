/**
* @file oaSkeleton.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/26/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaMatrix4f.h"
#include "oaResourse.h"

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

  WPtr<SkeletalNode> parent;
};

/**
 * @brief the skeleton for the animations
*/
class OA_CORE_EXPORT Skeleton :
  public Resourse
{
 public:

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kSkeleton;
  }

  FORCEINLINE Matrix4f//const Matrix4f&
  getBoneTransform(const String& name)
  {
    Matrix4f ans = Matrix4f::IDENTITY*m_globalInverse;
    auto wNode = m_boneMaping[name];
    while(!wNode.expired()){
      auto node = wNode.lock();
      ans = node->transform*ans;
      wNode = node->parent; 
    }
    return ans;
    //return m_boneMaping[name];
  }

  FORCEINLINE void
  addBone(SPtr<SkeletalNode> node)
  {
    m_boneMaping.insert({node->name,node});
  }

  FORCEINLINE SPtr<SkeletalNode>
  getRoot()
  {
    return m_skeleton;
  }

  FORCEINLINE const Matrix4f&
  getGlobalInverse()
  {
    return m_globalInverse;
  }

public:

  /**
   * @brief all the nodes of the skeleton
  */
  SPtr<SkeletalNode> m_skeleton;

  /**
   * @brief the mapping for the names of the bones
  */
  Map<String,WPtr<SkeletalNode>> m_boneMaping;

  /**
   * @brief the inverse of the root
  */
  Matrix4f m_globalInverse;
};

}
