/**
* @file oaObject.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModel.h"
#include "oaVector3f.h"
#include "oaMatrix4f.h"
#include "oaTree.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Object
{
 public:

  Object();

  /**
   * @brief updates the buffers, executed once eachFrame
  */
  void
  update();

  /**
   * @brief makes the object a sub object of this one
   * @param object 
  */
  void 
  attach(SPtr<Object> object);

  /**
   * @brief gets the transform Matrix of this object
   * @return 
  */
  Matrix4f
  getTransform();

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

  /**
   * @brief the name of the object in the editor
  */
  String name;

  /**
   * @brief the objects that are child of this
  */
  SPtr<Tree<Object>> subObjects;

 public:

  /**
   * @brief for sending the location to the shader
  */
  SPtr<Buffer> transformB;
};

}


