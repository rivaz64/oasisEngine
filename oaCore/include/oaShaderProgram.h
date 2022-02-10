/**
* @file oaShaderProgram.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT ShaderProgram
{
 public:
  
  /**
   * @brief attach a shader to this program
   * @param shader the shader to be attached
  */
  virtual void 
  attach(SPtr<Shader> shader){}

  /**
   * @brief sets this program to be used
  */
  virtual void
  set(){}
};

}



