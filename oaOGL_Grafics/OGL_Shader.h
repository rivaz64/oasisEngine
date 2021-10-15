/**
* @file oaOGL_Shader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesOGL.h"
#include "oaShader.h"


namespace oaEngineSDK{

class OGL_Shader:
  public Shader
{
 public:
  bool 
    compileFromFile(String file);

 protected:

  unsigned int id;

};

}

