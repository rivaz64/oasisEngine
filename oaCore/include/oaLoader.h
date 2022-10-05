/**
* @file oaLoader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/14/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

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

  /**
   * @brief checks what a file has
   * @param file th file to check
   * @return the things the file has
  */
  bool//LOADERFLAGS::E
  loadScene(const Path& file,WPtr<Actor> actor);

  /**
   * @brief loads certain things of a file
   * @param flags what things are going to be loaded
   * @param the model with the loaded things
  */
  void
  load(LOADERFLAGS::E flags);

  /**
   * @brief reads an image from a file
   * @param file the file with the image to load
   * @return if it loaded
  */
  bool
  loadTexture(const Path& path);

  /**
   * @brief reads a sound from a file
   * @param path 
   * @return 
  */
  bool 
  loadSound(const Path& path);

  /**
   * @brief detects what type of file it is and loads it
   * @param path 
   * @return 
  */
  bool 
  loadResource(const Path& path,WPtr<Actor> actor);

 private:

  uint8 m_loadedFlags = 0;
};

}


