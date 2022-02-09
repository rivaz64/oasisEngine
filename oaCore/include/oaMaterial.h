/**
* @file oaMaterial.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a class for materials
*/
class OA_CORE_EXPORT Material
{
 public:

  Material();

  /**
   * @brief sets this material to be used in the shader
  */
  void
  set();
  
  /**
   * @brief the diffuse texture of this material
  */
  SPtr<Texture> m_diffuse;

  /**
   * @brief the diffuse texture of this material
  */
  SPtr<Texture> m_specular;

  /**
   * @brief the diffuse texture of this material
  */
  SPtr<Texture> m_normalMap;

  /**
   * @brief the shaders program this material is going to be using
  */
  SPtr<ShaderProgram> m_program;

   String m_name;
};

}


