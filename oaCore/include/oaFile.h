/**
* @file oaFile.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace FILEFLAGS{
  enum E{
    READ = 1,
    WRITE = 2
  };
}

namespace oaEngineSDK{




/**
 * @brief interface class for managing input and output to files;
*/
class File
{
 public:


  /**
   * @brief opens a file to be read
   * @param path 
  */
  void
  open(const Path& path,FILEFLAGS::E flags);

  /**
   * @brief closes the file
  */
  void
  close();

  /**
   * @brief writes to the file
   * @param message 
  */
  void
  write(const String& message);

 private:
  void* file;
};

}


