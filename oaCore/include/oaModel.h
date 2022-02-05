/**
* @file oaModel.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaSphere.h"

namespace oaEngineSDK{

/**
 * @brief class for 3D models
*/
class OA_CORE_EXPORT Model
{
 public:

  /**
   * @brief default constructor for the model
  */
  Model() = default;

  ~Model() = default;


 private:
  
  /**
   * @brief the materials of the model
  */
  Vector<SPtr<Material>> m_materials;

  /**
   * @brief the meshes of the model
  */
  Vector<SPtr<Mesh>> m_meshes;

  String m_name;

  friend class Loader;
  friend class TestApp;
  friend class AnimationComponent;
  friend class GraphicsComponent;
  friend class SkeletalComponent;
};

}

