/**
* @file oaRenderer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/26/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaMatrix4f.h>

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

class OA_CORE_EXPORT Renderer
{
 public:

  void 
  init();

  void
  render(SPtr<Scene> scene,SPtr<Camera> camForView,SPtr<Camera> camForFrustrum);

  void
  meshesInFrustum(SPtr<Actor> actor,const Frustum& frustum,Vector<RenderData>& meshes);

 protected:
  
  SPtr<Buffer> m_globalTransformBuffer;

  SPtr<Buffer> m_viewBuffer;

  SPtr<Buffer> m_projectionBuffer;

  SPtr<Buffer> m_viewLocationBuffer;

  SPtr<Rasterizer> m_normalRasterizer;

  SPtr<Rasterizer> m_hairRasterizer;

  SPtr<Rasterizer> m_debugRasterizer;

};

}


