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
  
  /**
   * @brief compiles the shader
   * @return if the compilation was succesfull
  */
  virtual bool 
  compile() = 0;

  /**
   * @brief loads the code for the shader, it does not compile it
   * @param file 
   * @return if the file was loaded or not
  */
  virtual bool
  loadFromFile(String file) = 0;

 private:

  /**
   * @brief the code of the shader in its upper level language
  */
  String code;

};

}


