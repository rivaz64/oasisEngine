/**
* @file oaResoursemanager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaResourse.h"


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

  /**
   * @brief if this name is aready ocupied it ads a _n
   * @param name 
  */
  String 
  getUniqueName(String name);

  FORCEINLINE WPtr<Resourse>
  getResourse(const String& name)
  {
    return m_resourses[StringUtilities::getStringId(name)];
  }

  FORCEINLINE void
  registerResourse(const String& name, SPtr<Resourse> resourse)
  {
    String realName = getUniqueName(name);
    resourse->setName(realName);
    m_resourses.insert({StringUtilities::getStringId(realName),resourse});
    m_types[resourse->getType()].push_back(resourse);
  }

  FORCEINLINE void
  deleteAllResoursesOfType(RESOURSE_TYPE::E type)
  {
    auto& resourses = m_types[type];
    for(auto& resourse : resourses)
    {
      m_resourses.erase(StringUtilities::getStringId(resourse.lock()->getName()));
    }
    resourses.clear();
  }

  FORCEINLINE Vector<WPtr<Resourse>>
  getAllResoursesOfType(RESOURSE_TYPE::E type)
  {
    return m_types[type];
  }

 private:

  ///**
  //* @brief all the loaded meshes
  //*/
  //Map<uint64,WPtr<StaticMesh>> m_meshes;
  //
  ///**
  // * @brief all the loaded textures
  //*/
  //Map<uint64,WPtr<Texture>> m_textures;
  //
  ///**
  //* @brief all the loaded models
  //*/
  //Map<uint64,WPtr<Model>> m_models;
  //
  ///**
  // * @brief all the loaded vertex shaders
  //*/
  //Map<uint64,WPtr<Shader>> m_vertexShaders;
  //
  ///**
  // * @brief all the loaded pixel shaders
  //*/
  //Map<uint64,WPtr<Shader>> m_pixelShaders;
  //
  // /**
  // * @brief all the loaded pixel shaders
  //*/
  //Map<uint64,WPtr<Shader>> m_hullShaders;
  //
  // /**
  // * @brief all the loaded pixel shaders
  //*/
  //Map<uint64,WPtr<Shader>> m_domainShaders;
  //
  ///**
  // * @brief all the loaded pixel shaders
  //*/
  //Map<uint64,WPtr<ShaderProgram>> m_shaderPrograms;
  //
  ///**
  // * @brief all the loaded pixel shaders
  //*/
  //Map<uint64,Vector<WPtr<ShaderProgram>>> m_multiShaderPrograms;
  //
  ///**
  // * @brief all the materials
  //*/
  //Map<uint64,WPtr<Material>> m_materials;
  //
  ///**
  // * @brief all the loaded skeletons
  //*/
  //Map<uint64,WPtr<Skeleton>> m_skeletons;
  //
  ///**
  // * @brief all the loaded animations
  //*/
  //Map<uint64,WPtr<Animation>> m_animations;
  //
  ///**
  // * @brief all the loaded sounds
  //*/
  //Map<uint64,WPtr<Sound>> m_sounds;

   SPtr<Material> m_defaultMaterial;

  /**
   * @brief all the resourses for quick search
  */
  Map<uint64,SPtr<Resourse>> m_resourses;

  /**
   * @brief the resourses by type
  */
  Map<RESOURSE_TYPE::E,Vector<WPtr<Resourse>>> m_types;

  /**
   * @brief all the ids of the names
  */
  Set<uint64> m_ids;

  friend class Module<ResoureManager>;
  friend class TestApp;
  friend class Loader;
};

}


