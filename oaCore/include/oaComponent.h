/**
* @file oaComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief a component an Actor can have
*/
class OA_CORE_EXPORT Component :
  public enable_shared_from_this<Component>
{
 public:
  
  /**
   * @brief this executes when this is attached to an actor
   * @param actor 
  */
  virtual void
  onAttach(WPtr<Actor> actor) {};

  /**
   * @brief updates this component
   * @param actor the actor that has this component
  */
  virtual void
  update(WPtr<Actor> /*actor*/) {}

  virtual void
  save(Serializer& /*serializer*/){}

  virtual void
  load(Serializer& /*serializer*/){}

  /**
   * @brief get what is the type of this component
  */
  virtual COMPONENT_TYPE::E
  getType() {return COMPONENT_TYPE::kNone;}

  /**
   * @brief creates a component of type
   * @param type 
   * @return 
  */
  static SPtr<Component>
  create(uint32 type);

  static const Map<uint32,String>& 
  getNames();

public:
  WPtr<Actor> m_owner;
};

}


