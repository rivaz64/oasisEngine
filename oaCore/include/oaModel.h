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

  /**
   * @brief if the number of meshes is known
   * @param numOfMeshes 
  */
  Model(SIZE_T numOfMeshes);

  ~Model() = default;

  /**
   * @brief adds a mesh to this model
   * @param mesh the new mesh
  */
  FORCEINLINE void
  addMesh(SPtr<Mesh> mesh){
    m_meshes.push_back(mesh);
  }

  FORCEINLINE void
  addMaterial(SPtr<Material> material){
    m_materials.push_back(material);
  }

  FORCEINLINE SIZE_T
  getNumOfMeshes(){
    return m_meshes.size();
  }

  FORCEINLINE void
  setNumOfMeshes(SIZE_T n){
    return m_meshes.resize(n);
  }

  FORCEINLINE const SPtr<Mesh>&
  getMesh(SIZE_T n){
    return m_meshes[n];
  }

  FORCEINLINE const SPtr<Material>&
  getMaterial(SIZE_T n){
    return m_materials[n];
  }

  FORCEINLINE const SPtr<Material>&
  setMaterial(SPtr<Material> material,SIZE_T n){
    return m_materials[n] = material;
  }

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

