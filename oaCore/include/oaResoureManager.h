/**
* @file oaResoursemanager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaResourse.h"


namespace oaEngineSDK {

/**
 * @brief a singleton where all the resourses are going to be, every resourse
          is unique it would not load the same resourse 2 times
*/
class OA_CORE_EXPORT ResoureManager :
  public Module<ResoureManager>
{

 protected:

  ResoureManager() = default;

 public:

  /**
   * @brief loads the default things
  */
  void
  onStartUp() override;

  /**
   * @brief loads the defaault shaders
  */
  void
  loadDefaultShaders();

  /**
   * @brief loads the defaults textures
  */
  void
  loadDefaulTextures();

  /**
   * @brief creates the default materials
  */
  void
  generateDefaultMaterials();

  /**
   * @brief if this name is aready ocupied it ads a _n
   * @param name 
  */
  String 
  getUniqueName(String name);

  /**
   * @brief gets an existing resourse by name
   * @param name the name of the resource
   * @return if exist returns a resource, if not a null pointer
  */
  FORCEINLINE WPtr<Resourse>
  getResourse(const String& name)
  {
    auto id = StringUtilities::getStringId(name);
    if(m_resourses.find(id) != m_resourses.end()){
      return m_resourses[StringUtilities::getStringId(name)];
    }
    else{
      WPtr<Resourse>();
    }
  }

  /**
   * @brief adds a new resource 
   * @param name a proposed name, if its not unique it will add a counter
   * @param resourse the one to register
  */
  FORCEINLINE void
  registerResourse(const String& name, SPtr<Resourse> resourse)
  {
    String realName = getUniqueName(name);
    resourse->setName(realName);
    m_resourses.insert({StringUtilities::getStringId(realName),resourse});
    m_types[resourse->getType()].push_back(resourse);
  }

  /**
   * @brief deletes a resourse
   * @param name 
  */
  void
  deleteResourse(const String& name);

  /**
   * @brief deketes all the resourses of a same type
   * @param type 
  */
  FORCEINLINE void
  deleteAllResoursesOfType(RESOURSE_TYPE::E type)
  {
    auto& resourses = m_types[type];
    for(auto& resourse : resourses)
    {
      m_resourses.erase(StringUtilities::getStringId(resourse.lock()->getName()));
    }
    resourses.clear();
  }

  /**
   * @brief gets all the resources of a same type
   * @param type 
   * @return 
  */
  FORCEINLINE Vector<WPtr<Resourse>>
  getAllResoursesOfType(RESOURSE_TYPE::E type)
  {
    return m_types[type];
  }

  SPtr<Material> m_defaultMaterial;

 private:

  /**
   * @brief all the resourses for quick search
  */
  Map<uint64,SPtr<Resourse>> m_resourses;

  /**
   * @brief the resourses by type
  */
  Map<RESOURSE_TYPE::E,Vector<WPtr<Resourse>>> m_types;

  friend class Module<ResoureManager>;
};

}


