/**
* @file oaShaderProgram.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaShader.h"

namespace oaEngineSDK{

/**
 * @brief a shader for the complete pipeline
*/
class OA_CORE_EXPORT ShaderProgram :
  public Shader
{
 public:

  ShaderProgram(const Vector<WPtr<Shader>>& shaders);

  ShaderProgram() = default;

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kShader;
  }
  
  /**
   * @brief attach a shader to this program
   * @param shader the shader to be attached
  */
  virtual void 
  attach(WPtr<Shader> shader){}

  /**
   * @brief sets this program to be used
  */
  virtual void
  set(){}

  FORCEINLINE void
  setChannels(const Vector<String>& channels)
  {
    m_channels = channels;
  }

  FORCEINLINE const Vector<String>&
  getChannels()
  {
    return m_channels;
  }

 protected:
  
  /**
   * @brief the channels that this shader needs;
  */
  Vector<String> m_channels;
};

}



