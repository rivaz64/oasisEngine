/**
* @file oaLoader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/14/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaPath.h"

namespace LOADERFLAGS{
  enum E{
    kNone = 0,
    kMesh = 1,
    kTexture = 2,
    kSkeleton = 4,
    kAnimation = 8
  };
}

namespace oaEngineSDK{

/**
 * @brief class for reading external files
*/
class OA_CORE_EXPORT Loader
{
 public:

  Loader();

  ~Loader();

  /**
   * @brief checks what a file has
   * @param file th file to check
   * @return the things the file has
  */
  LOADERFLAGS::E
  checkForLoad(const Path& file);

  /**
   * @brief loads certain things of a file
   * @param flags what things are going to be loaded
   * @param the model with the loaded things
  */
  void
  load(LOADERFLAGS::E flags);

 private:
  
  /**
   * @brief loads the meshes of the models and adds them to the model
   * @param model 
  */
  void
  loadMeshes(SPtr<Model> model);

  /**
   * @brief loads textures and adds it to the model 
   * @param model 
  */
  void
  loadTextures(SPtr<Model> model);

  /**
   * @brief loads the skeleton
  */
  void
  loadSkeletons();

  /**
   * @brief loads the animations
  */
  void
  loadAnimations();

  const void* m_sceneI;

  uint8 m_loadedFlags = 0;

  Path m_file;

  void* m_importer;

  public:
  float m_importScale;
};

}


