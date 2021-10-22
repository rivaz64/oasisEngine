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

 public:

  friend class Module<ResoureManager>;

};

}


