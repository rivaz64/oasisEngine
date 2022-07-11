/**
* @file oaModel.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include "oaSphere.h"
#include "oaMesh.h"

namespace oaEngineSDK{

/**
 * @brief class for 3D models
*/
class OA_CORE_EXPORT Model :
  public Resourse
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

  void
  save(Serializer& serializer) override;

  void
  load(Serializer& serializer) override;

  /**
   * @brief adds a mesh to this model
   * @param mesh the new mesh
  */
  FORCEINLINE void
  addMesh(SPtr<Mesh<Vertex>> mesh){
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

  FORCEINLINE SIZE_T
  getNumOfMaterials(){
    return m_meshes.size();
  }

  FORCEINLINE void
  setNumOfMeshes(SIZE_T n){
    return m_meshes.resize(n);
  }

  FORCEINLINE const WPtr<Mesh<Vertex>>&
  getMesh(SIZE_T n){
    return m_meshes[n];
  }

  FORCEINLINE const WPtr<Material>&
  getMaterial(SIZE_T n){
    return m_materials[n];
  }

  FORCEINLINE const SPtr<Material>&
  setMaterial(WPtr<Material> material,SIZE_T n){
    m_materials[n] = material;
  }

  Vector3f 
  getCenter();

  float
  farestPoint(const Vector3f& pont);

 private:
  
  /**
   * @brief the materials of the model
  */
  Vector<WPtr<Material>> m_materials;

  /**
   * @brief the meshes of the model
  */
  Vector<SPtr<Mesh<Vertex>>> m_meshes;

  friend class Loader;
  friend class AnimationComponent;
  friend class GraphicsComponent;
  friend class SkeletalComponent;
  friend class ResoureManager;
};

}

