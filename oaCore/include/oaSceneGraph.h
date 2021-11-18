/**
* @file oaSceneGraph.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaTree.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

/**
 * @brief the hierarqui of the scene
*/
class OA_CORE_EXPORT SceneGraph
{
 public:

  /**
   * @brief draws everything on the scene
  */
  void
  draw();

  /**
   * @brief adds an abject to the scene
   * @param object 
  */
  void
  addToScene(const SPtr<Object> object);

 private:
  /**
   * @brief draws an object to the screen
   * @param object 
  */
  void
  drawObject(const SPtr<Tree<Object>> object,const Matrix4f& parentTransform);

 public:

  /**
   * @brief all the objects on the scene
  */
  //Vector<SPtr<Object>> objects;
  Tree<Object> objects;

  /**
   * @brief the shader to render normal stuff
  */
  SPtr<Shader> normalShader;

  /**
   * @brief the shader to render objects with no texture
  */
  SPtr<Shader> noTextureShader;
};

}


