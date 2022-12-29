/**
* @file oaResourse.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaSerializer.h"
#include <oaEventSystem.h>

namespace oaEngineSDK{

namespace RESOURSE_TYPE{
enum E{
  kNone = 0,
  kStaticMesh,
  kTexture,
  kModel,
  kShader,
  kVertexShader,
  kPixelShader,
  kHullShader,
  kDomaniShader,
  kShaderProgram,
  kMaterial,
  kSkeleton,
  kAnimation,
  kSound,
  kSkeletalMesh,
  kSkeletalModel,
  kActor,
  kImage
};
}

class OA_CORE_EXPORT Resourse :
  public SharedEnabled<Resourse>
{
 public:

  virtual void
  save(Serializer& /*serializer*/){}

  virtual void
  load(Serializer& /*serializer*/){}

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

  virtual RESOURSE_TYPE::E
  getType()
  {
    return RESOURSE_TYPE::kNone;
  }

public:

  oaEngineSDK::EventHandler<SPtr<Resourse>> m_onChanged; 

 private:
  String m_name;

  Path m_path;

  friend class Serializer;
};

}


