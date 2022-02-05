/**
* @file oaActor.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaMatrix4f.h"
#include "oaComponent.h"

namespace oaEngineSDK{

/**
 * @brief something that is on a scene
*/
class OA_CORE_EXPORT Actor :
  public SharedEnabled<Actor>
{
 public:

  Actor();

  /**
   * @brief makes the Actor a sub Actor of this one
   * @param Actor 
  */
  void 
  attach(SPtr<Actor> Actor);

  /**
   * @brief attaches a component
   * @param component 
  */
  void
  attachComponent(SPtr<Component> component);

  /**
   * @brief updates everything of this Actor
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
   * @brief getter for all the subActors of this Actor
   * @return 
  */
  const Vector<SPtr<Actor>>&
  getChilds();

  /**
   * @brief gets the transform Matrix of this Actor
   * @return 
  */
  Matrix4f
  getLocalTransform();

  /**
   * @brief the transform of this Actor in the world
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
    return cast<T>(m_components[temp.getType()]);
  }
 
 private:
  /**
   * @brief the name of the Actor in the editor
  */
  String m_name;

  /**
   * @brief the Actors that are child of this
  */
  Vector<SPtr<Actor>> m_subActors;

  /**
   * @brief the Actor this one is a child of
  */
  SPtr<Actor> m_parent;

  /**
   * @brief where the Actor is in a 3D space
  */
  Vector3f m_location;

  /**
   * @brief the scale compared with the original imported model
  */
  Vector3f m_scale;

  /**
   * @brief how the Actor is rotated
  */
  Vector3f m_rotation;

  /**
   * @brief the transform of this Actor with origin at his parent
  */
  Matrix4f m_localTransform;

  /**
   * @brief the transform of this Actor in the world
  */
  Matrix4f m_globalTransform = Matrix4f::IDENTITY;

  /**
   * @brief all the components this actor has
  */
  Map<COMPONENT_TYPE::E,SPtr<Component>> m_components;

  /**
   * @brief the dirty flag of the local and global matrix
  */
  //uint8 dirtyFlag = 0;
  friend class TestApp;
};

}


