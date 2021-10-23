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

class Object
{
 public:

  Object();

  /**
   * @brief the model that this object is using
  */
  SPtr<Model*> model;

  /**
   * @brief where the object is in a 3D space
  */
  Vector3f location;

 protected:

  /**
   * @brief for sending the location to the shader
  */
  SPtr<Buffer> locationB;
};

}


