/**
* @file oaObject.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaMatrix4f.h"
#include "oaComponent.h"
#include <memory>

namespace oaEngineSDK{

/**
 * @brief something that is on a scene
*/
class OA_CORE_EXPORT Object :
  public std::enable_shared_from_this<Object>
{
 public:

  Object();

  /**
   * @brief makes the object a sub object of this one
   * @param object 
  */
  void 
  attach(SPtr<Object> object);

  /**
   * @brief attaches a component
   * @param component 
  */
  void
  attachComponent(SPtr<Component> component);

  /**
   * @brief updates everything of this object
  */
  void 
  update();

  /**
   * @brief setter for the location;
   * @param _location 
  */
  void 
  setLocation(const Vector3f& _location);

  /**
   * @brief setter for the rotation
   * @param _rotation 
  */
  void
  setRotation(const Vector3f& _rotation);

  /**
   * @brief setter for the scale
   * @param _scale 
  */
  void 
  setScale(const Vector3f& _scale);

  /**
   * @brief getter for the location
   * @return 
  */
  const Vector3f&
  getLocation();

  /**
   * @brief getter for the rotation
   * @return 
  */
  const Vector3f&
  getRotation();

  /**
   * @brief getter for the scale
   * @return 
  */
  const Vector3f&
  getScale();

  /**
   * @brief getter for all the subobjects of this object
   * @return 
  */
  const Vector<SPtr<Object>>&
  getChilds();

  /**
   * @brief gets the transform Matrix of this object
   * @return 
  */
  Matrix4f
  getLocalTransform();

  /**
   * @brief the transform of this object in the world
   * @return 
  */
  Matrix4f
  getGlobalTransform();

  /**
   * @brief gets a specific component
   * @tparam T the component to get
   * @return 
  */
  template<class T>
  SPtr<T>
  getComponent(){
    T temp;
    return cast<T>(components[temp.getType()]);
  }

  /**
   * @brief the name of the object in the editor
  */
  String name;

  /**
   * @brief the objects that are child of this
  */
  Vector<SPtr<Object>> subObjects;

  /**
   * @brief the object this one is a child of
  */
  SPtr<Object> parent;

  /**
   * @brief for sending the location to the shader
  */
  SPtr<Buffer> transformB;

//for change to private
 public:
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
   * @brief the transform of this object with origin at his parent
  */
  Matrix4f localTransform;

  /**
   * @brief the transform of this object in the world
  */
  Matrix4f globalTransform = Matrix4f::IDENTITY;

  /**
   * @brief all the components this actor has
  */
  Map<COMPONENT_TYPE::E,SPtr<Component>> components;

  /**
   * @brief the dirty flag of the local and global matrix
  */
  uint8 dirtyFlag = 0;
};

}


