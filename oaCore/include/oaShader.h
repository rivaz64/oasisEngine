/**
* @file oaShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"

namespace oaEngineSDK{

/**
 * @brief class for all kinds of shaders
*/
class OA_CORE_EXPORT Shader :
  public Resourse
{
 public:
  
  /**
   * @brief default constructor para el shader
  */
  Shader() = default;

   virtual ~Shader() = default;

  /**
   * @brief compiles the sahder
   * @param file the file where the shader is
   * @return if it was compiled correctly
  */
  virtual bool 
  compileFromFile(String file) {return true;}

  virtual void
  set() {}

};

}


