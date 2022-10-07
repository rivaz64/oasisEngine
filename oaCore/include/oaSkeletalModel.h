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
  addMesh(WPtr<SkeletalMesh> mesh){
    m_meshes.push_back(mesh);
  }

  FORCEINLINE void
  addMaterial(WPtr<Material> material){
    m_materials.push_back(material);
  }

  FORCEINLINE void
  setSkeleton(WPtr<Skeleton> skeleton){
    m_skeleton = skeleton;
  }

  FORCEINLINE void
  setAnimation(WPtr<Animation> animation){
    m_animation = animation;
  }

  FORCEINLINE WPtr<SkeletalMesh>
  getMesh(SIZE_T n){
    return m_meshes[n];
  }

  FORCEINLINE WPtr<Material>
  getMaterial(SIZE_T n){
    return m_materials[n];
  }

  FORCEINLINE WPtr<Skeleton>
  getSkeleton(){
    return m_skeleton;
  }

  FORCEINLINE WPtr<Animation>
  getAnimation(){
    return m_animation;
  }

  FORCEINLINE SIZE_T
  getNumOfMeshes(){
    return m_meshes.size();
  }

 private:
  
  /**
   * @brief the materials of the model
  */
  Vector<WPtr<Material>> m_materials;

  /**
   * @brief the meshes of the model
  */
  Vector<WPtr<SkeletalMesh>> m_meshes;

  /**
   * @brief the skeleton of this model
  */
  WPtr<Skeleton> m_skeleton;

  /**
   * @brief the animation of this model
  */
  WPtr<Animation> m_animation;

};

}



