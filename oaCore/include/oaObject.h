/**
* @file oaObject.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModel.h"
#include "oaVector3f.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Object
{
 public:

  Object();

  void
  update();

  /**
   * @brief the model that this object is using
  */
  SPtr<Model> model;

  /**
   * @brief where the object is in a 3D space
  */
  Vector3f location;

  /**
   * @brief the scale compared with the original imported model
  */
  Vector3f scale;

  /**
   * @brief how the object is rotated
  */
  Vector3f rotation;

 public:

  /**
   * @brief for sending the location to the shader
  */
  SPtr<Buffer> transformB;
};

}


