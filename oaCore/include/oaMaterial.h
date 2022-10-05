/**
* @file oaMaterial.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include "oaFlags.h"
#include "oaRasterizerState.h"
#include <oaColor.h>

namespace oaEngineSDK{

namespace GBUFFER_FLAGS{
enum E {
  kNone = 0,
  kDiffuse = 1,
  kNormals = 2,
  kSpecular = 4,
  kEmisive = 8
};
}

/**
 * @brief a class for materials
*/
class OA_CORE_EXPORT Material :
  public Resourse 
{
 public:

  Material() = default;

  void
  save(Serializer& serializer) override;

  void
  load(Serializer& serializer) override;

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kMaterial;
  }

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
  setTexture(const String& channel,WPtr<Texture>  texture);

  /**
   * @brief gets a texture being used by this material
   * @param type the type of texture to get
   * @return the texture of that type
  */
  WPtr<Texture>
  getTexture(const String& channel);

  void
  setColor(const String& channel,const Color& color);

  bool
  getColor(const String& channel,Color& color);
  
  Vector<String>
  getTextureChannels();

  /**
   * @brief sets the shader to be used by this material
   * @param shader 
  */
  FORCEINLINE void
  setShader(uint32 shader)
  {
    m_shader = shader;
  }

  FORCEINLINE uint32
  getShader()
  {
    return m_shader;
  }

  FORCEINLINE bool
  getCastShadows()
  {
    return m_castShadows; 
  }

  CULLING::E m_culling;

  FILL_MODE::E m_fillMode;

 private:
  /**
   * @brief the textures used for this shader
  */
  Map<String,WPtr<Texture>> m_textures;

  /**
   * @brief the colors used for this shader
  */
  Map<String,Color> m_colors;

  /**
   * @brief the shaders program that is going to be using
  */
  uint32 m_shader;

  /**
   * @brief if meshes with this material cast shadows
  */
  bool m_castShadows = true;
};

}


