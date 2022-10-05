#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"

namespace oaEngineSDK
{

class OA_CORE_EXPORT SkeletalModel :
  public Resourse
{
public:

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kSkeletalModel;
  }

  FORCEINLINE void
  setMesh(WPtr<SkeletalMesh> mesh){
    m_mesh = mesh;
  }

  FORCEINLINE void
  setMaterial(WPtr<Material> material){
    m_material = material;
  }

  FORCEINLINE WPtr<SkeletalMesh>
  getMesh(){
    return m_mesh;
  }

  FORCEINLINE WPtr<Material>
  getMaterial(){
    return m_material;
  }

 private:
  
  /**
   * @brief the materials of the model
  */
  WPtr<Material> m_material;

  /**
   * @brief the meshes of the model
  */
  WPtr<SkeletalMesh> m_mesh;

};

}



