/**
* @file oaTexture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/14/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaPath.h"

namespace LOADERFLAGS{
  enum E{
    NONE = 0,
    MESH = 1,
    TEXTURE = 2,
    SKELETON = 4,
    ANIMATION = 8
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
  
  void
  loadMeshes(SPtr<Model> model);

  void
  loadTextures(SPtr<Model> model);

  void
  loadSkeletons(SPtr<Model> model);

  void
  loadAnimations(SPtr<Model> model);

  const void* sceneI;

  uint8 loadedFlags = 0;

  Path file;

  void* importer;
};

}


