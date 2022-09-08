/**
* @file oaShaderProgram.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/6/2022
*/

#pragma once

#include "oaShader.h"

namespace oaEngineSDK
{

/**
 * @brief a shader that can adapt if some variables are mising
*/
class OA_CORE_EXPORT AdaptativeShader :
  public Shader
{
 public:

  AdaptativeShader(WPtr<Shader> vertexShader) :
    m_vertexShader(vertexShader) {}

  AdaptativeShader() = default;

  /**
   * @brief compiles the name file with all the combinations of all defines
   * @param name 
   * @param allDefines 
   * @return 
  */
  bool
  compile(const String& name, const Vector<String>& allDefines);

  void
  set(uint32 flags);

 protected:

  Vector<SPtr<Shader>> m_shaders;

  WPtr<Shader> m_vertexShader;
};

}


