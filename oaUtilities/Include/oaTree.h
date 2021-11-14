/**
 * @file oaTree.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK {

/**
 * @brief data structor of a tree
 * @tparam T the type of data that the tree contains
*/
template<class T>
class Tree{

  /**
   * @brief the data of the root of this tree
  */
  SPtr<T> data;

  /**
   * @brief the childs of this tree
  */
  Vector<SPtr<Tree<T>>> childs;

};
}