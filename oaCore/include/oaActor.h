/**
* @file oaActor.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaTransform.h>
#include "oaComponent.h"
#include "oaResourse.h"

namespace oaEngineSDK{

/**
 * @brief something that is on a scene
*/
class OA_CORE_EXPORT Actor :
  public SharedEnabled<Actor>, public Resourse
{
 public:

  Actor() : m_localTransform(){}

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

  FORCEINLINE Transform&
  GetActorTransform(){
    return m_localTransform;
  }

  /**
   * @brief getter for all the subActors of this Actor
   * @return 
  */
  const Vector<SPtr<Actor>>&
  getChilds();

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
    if(m_components.find(temp.getType()) == m_components.end()){
      return SPtr<T>();
    }
    return cast<T>(m_components[temp.getType()][0]);
  }

  template<class T>
  Vector<SPtr<Component>>
  getComponents(){
    T temp;
    if(m_components.find(temp.getType()) == m_components.end()){
      return Vector<SPtr<Component>>();
    }
    return m_components[temp.getType()];
  }
 
 private:

  /**
   * @brief the Actors that are child of this
  */
  Vector<SPtr<Actor>> m_subActors;

  /**
   * @brief the local transform of this actor
  */
  Transform m_localTransform;

  /**
   * @brief the transform of this Actor in the world
  */
  Matrix4f m_globalTransform = Matrix4f::IDENTITY;

  /**
   * @brief all the components this actor has
  */
  Map<COMPONENT_TYPE::E,Vector<SPtr<Component>>> m_components;

  /**
   * @brief the dirty flag of the local and global matrix
  */
  //uint8 dirtyFlag = 0;
};

}


