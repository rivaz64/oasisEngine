#pragma once
#include "oaPrerequisitesUtilities.h"
namespace oaEngineSDK{

class WorldState
{
 public:

  /**
   * @brief defines a condicion of the world
   * @param condicion 
  */
  static void
  defineCondicion(uint32 condicion);

  /**
   * @brief add a condicion to concider
   * @param the condicion of the user
  */
  void
  addCondicion(uint32 condicion);

  /**
   * @brief set a condicion as true or false
   * @param the condicion of the user
   * @param if ths condicion is set or not
  */
  void
  setCondicion(uint32 condicion, bool isTrue);

  /**
   * @brief gets if a condicion is true or false
   * @param condicion 
   * @return 
  */
  bool
  getCondicion(uint32 condicion);

  /**
   * @brief the number of diferences between 2 world states
   * @param other 
   * @return 
  */
  uint32 
  getNumOfDiferences(const WorldState& other);

 private:

  /**
   * @brief gets the flag from the user defined
   * @param userFlag 
   * @return 
  */
  uint32
  getFlag(uint32 userFlag);



  /**
   * @brief pams the flag with user flags
   * first is the user flag
   * second is the world state flag 
  */
  static Vector<uint32> m_flagMapping;

  /**
   * @brief the condicions to concider in this world state
  */
  uint32 m_flagMask;

  /**
   * @brief the condicions in the world that can be true or not
  */
  uint32 m_wordlStateFlags;
};

}


