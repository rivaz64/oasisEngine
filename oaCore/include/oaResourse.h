/**
* @file oaResourse.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaPath.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Resourse
{
 public:

  FORCEINLINE const String&
  getName(){
    return m_name;
  }

  FORCEINLINE void
  setName(const String& name){
    m_name = name;
  }

  FORCEINLINE const Path&
  getPath(){
    return m_path;
  }

  FORCEINLINE void
  setPath(const Path& path){
    m_path = path;
  }

 private:
  String m_name;

  Path m_path;

  friend class Serializer;
};

}


