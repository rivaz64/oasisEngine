/**
* @file oaModel.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include "oaSphere.h"

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

  ~Model() = default;

  void
  onSave(Serializer& serializer) override;

  void
  load(Serializer& serializer) override;

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kModel;
  }

  /**
   * @brief adds a mesh to this model
   * @param mesh the new mesh
  */
  FORCEINLINE void
  setMesh(WPtr<StaticMesh> mesh){
    m_mesh = mesh;
  }

  FORCEINLINE void
  setMaterial(WPtr<Material> material){
    m_material = material;
  }

  FORCEINLINE WPtr<StaticMesh>
  getMesh(){
    return m_mesh;
  }

  FORCEINLINE WPtr<Material>
  getMaterial(){
    return m_material;
  }

  Vector3f 
  getCenter();

  float
  farestPoint(const Vector3f& pont);

 private:
  
  /**
   * @brief the materials of the model
  */
  WPtr<Material> m_material;

  /**
   * @brief the meshes of the model
  */
  WPtr<StaticMesh> m_mesh;
};

}

