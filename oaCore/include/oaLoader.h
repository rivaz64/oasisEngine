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

  uint8 m_loadedFlags = 0;

  Path m_file;
};

}


