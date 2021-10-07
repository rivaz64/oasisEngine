/**
* @file oaShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief class for all kinds of shaders
*/
class Shader
{
 public:
  
  virtual bool 
  compile();


 private:

  /**
   * @brief the code of the shader in its upper level language
  */
  String code;

};

}


