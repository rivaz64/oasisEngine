/**
* @file oaSkeletalMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/11/2022
*/

#pragma once

#include "oaMesh.h"

namespace oaEngineSDK{

class SkeletalMesh :
  public Mesh
{
 public:

  void 
  create() override;

  void 
  set() override;

 public:

  /**
   * @brief the vertices of this mesh
  */
  Vector<AnimationVertex> m_vertices;

  /**
   * @brief the buffer for the bones
  */
  SPtr<Buffer> m_bonesB;

  /**
   * @brief the bones of this mesh
  */
  Vector<Matrix4f> m_bones;

  Vector<Matrix4f> m_ofset;

  /**
   * @brief the names of the bones used by this mesh
  */
  Map<String,uint32> m_boneMaping;

  friend class Loader;
  friend class AnimationComponent;
};

}


