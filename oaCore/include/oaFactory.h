#pragma once
#include "oaPrerequisitesCore.h"

#define REGISTER_CLASS(parentName,classname) namespace { auto registery_##classname = ConcreteFactory<##parentName##,##classname##>(#classname); }

namespace oaEngineSDK
{

/**
 * @brief a class for the factory pattern
 * @tparam T the parent class of witch this factory is going to build childs of
*/
template<typename T>
class Factory
{
  /**
   * @brief gets the fatories for eviting creation error
   * @return 
  */
  static Map<uint32,Factory<T>*>& getRegister() {
    static Map<uint32,Factory<T>*> factories{};
		return factories;
	}
public:
  /**
   * @brief gets the names of the classes
   * @return 
  */
  static Map<uint32,String>& getNames() {
    static Map<uint32,String> names{};
		return names;
	}

public:

  /**
   * @brief gets the names of the classes
   * @return 
  */
  static const Map<uint32,String>& getClassNames() {
		return getNames();
	}

  /**
   * @brief creates an instance of a subclass this factory is of
   * @param type the type of the subclass
   * @return the instance of the subclass
  */
  static SPtr<T> 
  create(uint32 type)
  {
    return getRegister()[type]->getInstance();
  }

  /**
   * @brief registers a new type
   * @param typeId the id of this type
   * @param constructor the constructor of this type
  */
  static void
  registerSubtype(uint32 typeId,String name,Factory<T>* factory)
  {
    print("registered" + StringUtilities::intToString(typeId));
    getRegister().insert({typeId,factory});
    getNames().insert({typeId,name});
  }

  /**
   * @brief registers a new type
   * @param typeId the id of this type
   * @param constructor the constructor of this type
  */
  static void
  registerSubtype(uint32 typeId, Factory<T>* factory)
  {
    print("registered" + StringUtilities::intToString(typeId));
    getRegister().insert({typeId,factory});
  }

  virtual SPtr<T> 
  getInstance() = 0;
};

/**
 * @brief subclass
 * @tparam T the parent class
 * @tparam S the sub class
*/
template<typename T, typename S>
class ConcreteFactory :
  public Factory<T>
{
public:
  ConcreteFactory()
  {
    auto subclass = makeSPtr<S>();
    Factory<T>::registerSubtype((uint32)subclass->getType(),this);
  }

  ConcreteFactory(String name)
  {
    auto subclass = makeSPtr<S>();
    Factory<T>::registerSubtype((uint32)subclass->getType(),name,this);
  }

  SPtr<T> 
  getInstance() override
  {
    return makeSPtr<S>();
  }
};

}

