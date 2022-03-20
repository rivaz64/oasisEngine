/**
* @file oaScene.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

struct RenderData{

  RenderData();

  RenderData(SPtr<Mesh> mesh,SPtr<Material> material, const Matrix4f& transform) :
    m_mesh(mesh),
    m_material(material),
    m_transform(transform) {}

  SPtr<Mesh> m_mesh;

  SPtr<Material> m_material;

  Matrix4f m_transform;
};

class OA_CORE_EXPORT Scene
{
 public:

  void
  init();

  FORCEINLINE SPtr<Actor> 
  getRoot(){
    return m_root;
  }

  void
  meshesToRender(SPtr<Actor> actor,const Frustum& frustum,Vector<RenderData>& meshes,Vector<RenderData>& transparentMeshes);

 private:

  SPtr<Actor> m_root;

};

}


