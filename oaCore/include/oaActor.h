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
  public Resourse
{
 public:

  Actor() : m_localTransform(){}

  void
  save(Serializer& serializer) override;

  void
  load(Serializer& serializer) override;

  RESOURSE_TYPE::E
  getType() override;

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

  void 
  postUpdate();

  FORCEINLINE Transform&
  GetActorTransform(){
    return m_localTransform;
  }

  void
  unattach(WPtr<Actor> child);

  /**
   * @brief getter for all the subActors of this Actor
   * @return 
  */
  const Vector<SPtr<Actor>>&
  getChilds();

  void
  setActorLocation(const Vector3f& v);

  void
  setActorScale(const Vector3f& v);

  void
  setActorRotation(const Vector3f& v);

  /**
   * @brief the transform of this Actor in the world
   * @return 
  */
  Matrix4f
  getGlobalTransform();

  /**
   * @brief gets the location relative to the origin
   * @return 
  */
  Vector3f
  getGlobalLocation();

  /**
   * @brief gets the scale in the world
   * @return 
  */
  Vector3f
  getGlobalScale();

  Vector3f
  getGlobalRotation();

  Vector3f
  getLocalLocation();

  Vector3f
  getLocalScale();

  Vector3f
  getLocalRotation();

  /**
   * @brief gets a specific component
   * @tparam T the component to get
   * @return 
  */
  template<class T>
  WPtr<T>
  getComponent(){
    T temp;
    if(m_components.find(temp.getType()) == m_components.end()){
      return WPtr<T>();
    }
    return cast<T>(m_components[temp.getType()][0]);
  }

  template<class T>
  const Vector<SPtr<Component>>&
  getComponents(){
    T temp;
    if(m_components.find(temp.getType()) == m_components.end()){
      return Vector<SPtr<Component>>();
    }
    return m_components[temp.getType()];
  }

  FORCEINLINE bool
  hasChanged()
  {
    return m_localTransform.m_changed;
  }

  FORCEINLINE WPtr<Actor>
  getParent()
  {
    return m_parent;
  }
  
  SIZE_T
  getNumOfComponents();

  FORCEINLINE const Vector<WPtr<GraphicsComponent>>&
  getGraphicComponents()
  {
    return m_graphicComponents;
  }
  FORCEINLINE void
  addGraphicComponent(WPtr<GraphicsComponent> component)
  {
    m_graphicComponents.push_back(component);
  }
 
 private:

  /**
   * @brief the Actors that are child of this
  */
  Vector<SPtr<Actor>> m_subActors;

  /**
   * @brief the parent of this actor
  */
  WPtr<Actor> m_parent;

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

  private:
  /**
   * @brief all the components that are going to be rendered
  */
  Vector<WPtr<GraphicsComponent>> m_graphicComponents;

  /**
   * @brief the dirty flag of the local and global matrix
  */
  //uint8 dirtyFlag = 0;

  friend class GraphicsComponent;

  friend class Component;

};

}


