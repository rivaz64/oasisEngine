/**
 * @file oaTree.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include<memory>

namespace oaEngineSDK {

/**
 * @brief data structor of a tree
 * @tparam T the type of data that the tree contains
*/
template<class T>
class Tree:
  public std::enable_shared_from_this<Tree<T>>
{

 public:

  

 public:
  /**
   * @brief the data of the root of this tree
  */
  T data;

  /**
   * @brief the childs of this tree
  */
  Vector<SPtr<Tree<T>>> childs;

  /**
   * @brief the parent of this tree
  */
  SPtr<Tree<T>> parent;


  /**
   * @brief inserts a value into the Tree
   * @param value 
  */
  void
  insert(SPtr<T> value){
    auto newNode = newSPtr<Tree<T>>();
    newNode->data = value;
    newNode->parent = this->shared_from_this();
    childs.push_back(newNode);
  }
};
}