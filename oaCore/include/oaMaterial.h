/**
* @file oaMaterial.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaResourse.h"

namespace oaEngineSDK{

namespace TEXTURE_TYPE{
enum E{
  kDiffuse = 0,
  kSpecular,
  kNormalMap,
  kDepthMap
};
}

namespace SHADER_TYPE{
enum E {
  kNormal = 0,
  kAnimation,
  kParalax,
  kTransparent,
  kDebug
};
}

/**
 * @brief a class for materials
*/
class OA_CORE_EXPORT Material :
  public Resourse 
{
 public:

  Material();

  /**
   * @brief sets this material to be used in the shader
  */
  void
  set();

  /**
   * @brief sets a texture to be used by this materiañ
   * @param type what type of texture it is
   * @param texture the texture
  */
  void
  setTexture(TEXTURE_TYPE::E type,SPtr<Texture>  texture);

  /**
   * @brief gets a texture being used by this material
   * @param type the type of texture to get
   * @return the texture of that type
  */
  SPtr<Texture>
  getTexture(TEXTURE_TYPE::E type);
  
  Vector<TEXTURE_TYPE::E>
  getTextureTypes();

  /**
   * @brief sets the shader to be used by this material
   * @param shader 
  */
  FORCEINLINE void
  setShader(SHADER_TYPE::E shader){
    m_shader = shader;
  }

  FORCEINLINE SHADER_TYPE::E
  getShader(){
    return m_shader;
  }

 private:
  /**
   * @brief the textures used for this shader
  */
  Map<TEXTURE_TYPE::E,SPtr<Texture>> m_textures;

  /**
   * @brief the shaders program that is going to be using
  */
  SHADER_TYPE::E m_shader;
  
};

}


