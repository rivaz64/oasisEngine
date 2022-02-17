/**
* @file oaPath.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/15/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Path
{
 public:
  Path() = default;

  ~Path() = default;

  bool
  searchForPath();

  FORCEINLINE WString
  getCompletePath() const
  {
    return completePath;
  }

  void
  setCompletePath(WString path);

  void
  setCompletePath(String path);

  FORCEINLINE WString
  getDrive() const
  {
    return drive;
  }

  FORCEINLINE WString
  getDirection() const
  {
    return direction;
  }

  FORCEINLINE WString
  getName() const
  {
    return name;
  }

  FORCEINLINE WString
  getExtencion() const
  {
    return extencion;
  }

 private:

  WString completePath;

  UNICHAR drive[_MAX_DRIVE];
  UNICHAR direction[_MAX_DIR];
  UNICHAR name[_MAX_FNAME];
  UNICHAR extencion[_MAX_EXT];
  
};

}


