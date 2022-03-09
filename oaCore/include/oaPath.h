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
    return m_extencion;
  }

 private:

  WString m_completePath;

  WString m_drive;
  WString m_direction;
  WString m_name;
  WString m_extencion;
  
};

}


