/**
* @file oaResoursemanager.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"


namespace oaEngineSDK {

/**
 * @brief a singleton where all the resourses are going to be, every resourse
          is unique it would not load the same resourse 2 times
*/
class OA_UTILITY_EXPORT oaResoureManager :
  public Module<oaResoureManager>
{
  
  void loadTexture() {};
};

}


