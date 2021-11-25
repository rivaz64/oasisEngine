/**
* @file oaResoursemanager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaMesh.h"
#include "oaTexture.h"
#include "oaModel.h"

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
   * @brief loads a texture from a file
   * @return 
  */
  bool
  loadTexture(const String& file);

  /**
   * @brief loads the default things
  */
  void
  onStartUp() override;

  /**
   * @brief generates a circle
   * @param n the number of sides the circle has
  */
  void
  generateCircle(const uint8 n);

  /**
   * @brief generates a n poligon piramid
   * @param n the number of sides of the base of the piramid
  */
  void
  generateCone(const uint8 n);

  /**
   * @brief generates a n poligon cilinder
   * @param n the number of sides of the base of the cilinder
  */
  void
  generateCilinder(const uint8 n);

 private:

  /**
   * @brief generates a 1*1 plane
  */
  void 
  generatePlane();

  /**
   * @brief generates a 1*1*1 cube
  */
  void
  generateCube();

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

  void
  generateDefaultMaterial();

 public:

  /**
  * @brief all the loaded meshes
  */
   Map<String,SPtr<Mesh>> meshes;

  /**
   * @brief all the loaded textures
  */
  Map<String,SPtr<Texture>> textures;

  /**
  * @brief all the loaded models
  */
  Map<String,SPtr<Model>> models;

  /**
   * @brief all the loaded vertex shaders
  */
  Map<String,SPtr<Shader>> vertexShaders;

  /**
   * @brief all the loaded pixel shaders
  */
  Map<String,SPtr<Shader>> pixelShaders;

  /**
   * @brief all the materials
  */
  Map<String,SPtr<Material>> materials;



 public:

  friend class Module<ResoureManager>;

};

}


