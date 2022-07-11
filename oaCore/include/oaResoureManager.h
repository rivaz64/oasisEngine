/**
* @file oaResoursemanager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"



namespace oaEngineSDK {

/**
 * @brief a singleton where all the resourses are going to be, every resourse
          is unique it would not load the same resourse 2 times
*/
class OA_CORE_EXPORT ResoureManager :
  public Module<ResoureManager>
{

 protected:

  ResoureManager() = default;

 public:

  /**
   * @brief loads the default things
  */
  void
  onStartUp() override;

//  /**
//   * @brief generates a circle
//   * @param n the number of sides the circle has
//  */
//  void
//  generateCircle(const uint8 n);
//
//  /**
//   * @brief generates a n poligon piramid
//   * @param n the number of sides of the base of the piramid
//  */
//  void
//  generateCone(const uint8 n);
//
//  /**
//   * @brief generates a n poligon cilinder
//   * @param n the number of sides of the base of the cilinder
//  */
//  void
//  generateCilinder(const uint8 n);
//
//  /**
//   * @brief generates a torus
//   * @param n the sides of the main circunference
//   * @param m the sides of the circunferences surrounding the main circunference
//   * @param ratio at one there is no hole
//  */
//  void
//  generateTorus(const uint8 n, const uint8 m, const float ratio);
//
// private:
//
  /**
   * @brief generates a 1*1 plane
  */
  void 
  generateQuad();

  /**
   * @brief generates a 1*1*1 cube
  */
  void
  generateCube();

  void
  generateTriangle();

  /**
   * @brief loads the defaault shaders
  */
  void
  loadDefaultShaders();

  /**
   * @brief loads the defaults textures
  */
  void
  loadDefaulTextures();

  /**
   * @brief creates the default materials
  */
  void
  generateDefaultMaterials();

  /**
   * @brief does spatial separation to a model
   * @param model 
  */
  void
  separate(SPtr<Model> model, 
           const Vector3f& center, 
           Vector<SPtr<Model>>& division,
           float size);

 public:

  /**
  * @brief all the loaded meshes
  */
  Map<String,SPtr<Mesh<Vertex>>> m_meshes;

  /**
   * @brief all the loaded textures
  */
  Map<String,SPtr<Texture>> m_textures;

  /**
  * @brief all the loaded models
  */
  Map<String,SPtr<Model>> m_models;

  /**
   * @brief all the loaded vertex shaders
  */
  Map<String,SPtr<Shader>> m_vertexShaders;

  /**
   * @brief all the loaded pixel shaders
  */
  Map<String,SPtr<Shader>> m_pixelShaders;

   /**
   * @brief all the loaded pixel shaders
  */
  Map<String,SPtr<Shader>> m_hullShaders;

   /**
   * @brief all the loaded pixel shaders
  */
  Map<String,SPtr<Shader>> m_domainShaders;

  /**
   * @brief all the loaded pixel shaders
  */
  Map<String,SPtr<ShaderProgram>> m_shaderPrograms;

  /**
   * @brief all the loaded pixel shaders
  */
  Map<String,Vector<SPtr<ShaderProgram>>> m_multiShaderPrograms;

  /**
   * @brief all the materials
  */
  Map<String,SPtr<Material>> m_materials;

  /**
   * @brief all the loaded skeletons
  */
  Map<String,SPtr<Skeleton>> m_skeletons;

  /**
   * @brief all the loaded animations
  */
  Map<String,SPtr<Animation>> m_animations;

  /**
   * @brief all the loaded sounds
  */
  Map<String,SPtr<Sound>> m_sounds;

  friend class Module<ResoureManager>;
  friend class TestApp;
  friend class Loader;
};

}


