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

 public:

  /**
   * @brief inserts a value into the Tree
   * @param value 
  */
  void
  insert(SPtr<T> value){
    auto newNode = newSPtr<Tree<T>>();
    newNode->data = value;
    childs.push_back(newNode);
  }

 public:
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