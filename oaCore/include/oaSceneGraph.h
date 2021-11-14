/**
* @file oaSceneGraph.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief the hierarqui of the scene
*/
class OA_CORE_EXPORT SceneGraph
{
 public:

  /**
   * @brief draws an object to the screen
   * @param object 
  */
  void
  drawObject(SPtr<Object> object);

};

}


