#pragma once
#include "oaIAForDec.h"
#include "oaWorldState.h"
namespace oaEngineSDK{

class Action
{
 public:

 private:

  /**
   * @brief the things necesary for executing this action
  */
  WorldState precondicion;

  /**
   * @brief the changes that are the result of this action
  */
  WorldState effects;


};

}


