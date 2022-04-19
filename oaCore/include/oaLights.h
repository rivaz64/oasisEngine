/**
* @file oaLights.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector4f.h"
#include "oaColor.h"

namespace oaEngineSDK{

/**
 * @brief structure for a directional light
*/
struct DirectionalLight{
  
  /**
   * @brief the direction of the light
  */
  Vector4f direction;

  /**
   * @brief the color of the light
  */
  Color color;

};

/**
 * @brief the structure fir a point that is a light source
*/
struct PointLight{
  
  /**
   * @brief the color of the light
  */
  Color color;

  /**
   * @brief the point where the light is
  */
  Vector3f location;

  /**
   * @brief how far he light can reach
  */
  float intensity;
};

}
