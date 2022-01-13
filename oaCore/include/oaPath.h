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

  FORCEINLINE String
  getCompletePath() const
  {
    return completePath;
  }

  void
  setCompletePath(String path);

  FORCEINLINE String
  getDrive() const
  {
    return drive;
  }

  FORCEINLINE String
  getDirection() const
  {
    return direction;
  }

  FORCEINLINE String
  getName() const
  {
    return name;
  }

  FORCEINLINE String
  getExtencion() const
  {
    return extencion;
  }

 private:

  String completePath;

  char drive[_MAX_DRIVE];
  char direction[_MAX_DIR];
  char name[_MAX_FNAME];
  char extencion[_MAX_EXT];
  
};

}


