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
 * @brief a light that comes in all directions
*/
struct AmbientLight
{
  /**
   * @brief the color of the light
  */
  Color color = Color::WHITE;
};

/**
 * @brief structure for a directional light
*/
struct DirectionalLight
{
  /**
   * @brief the color of the light
  */
  Color color = Color::WHITE;

  /**
   * @brief the direction of the light
  */
  Vector4f direction = Vector4f(1,-1,0,0);
};

/**
 * @brief the structure fir a point that is a light source
*/
struct PointLight
{
  /**
   * @brief the color of the light
  */
  Color color = Color::WHITE;

  /**
   * @brief the point where the light is
  */
  Vector3f location;

  /**
   * @brief how far he light can reach
  */
  float intensity;
};

struct SpotLight
{
  /**
   * @brief the color of the light
  */
  Color color = Color::WHITE;

  /**
   * @brief the direction the light is pointed at
  */
  Vector4f direction = Vector4f(1,0,0,0);

  /**
   * @brief the point where the light is
  */
  Vector3f location;

  /**
   * @brief how far he light can reach
  */
  float intensity;

  /**
   * @brief the angle of the light 
  */
  float angle;
};

}
