/**
 * @file oaStdHeaders.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/11/2021
 */

#pragma once

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <map>

namespace oaEngineSDK {
/**
 * @brief wraper of the std::vector, can be changed in the future
 * @tparam T
*/
template <class T>
using Vector = std::vector<T>;

/**
 * @brief wraper of the std::list, can be changed in the future
 * @tparam T
*/
template <class T>
using List = std::list<T>;

/**
 * @brief wraper of the std::stack, can be changed in the future
 * @tparam T
*/
template <class T>
using Stack = std::stack<T>;

/**
 * @brief wraper of the std::queue, can be changed in the future
 * @tparam T
*/
template <class T>
using Queue = std::queue<T>;

/**
 * @brief wraper of the std::priority_queue, can be changed in the future
 * @tparam T
*/
template <class T>
using PriorityQueue = std::priority_queue<T>;

/**
 * @brief wraper of the std::priority_queue, can be changed in the future
 * @tparam T
*/
template <class T>
using PriorityQueue = std::priority_queue<T>;

/**
 * @brief wraper of the std::string, can be changed in the future
 * @tparam T
*/
using String = std::string;

/**
 * @brief wraper of the std::wstring, can be changed in the future
 * @tparam T
*/
using WString = std::wstring;

/**
 * @brief wraper of the std::shared_ptr, can be changed in the future
 * @tparam T
*/
template <class T>
using SPtr = std::shared_ptr<T>;

/**
* @brief wraper of the std::make_shared
* @tparam T
*/
template <class T>
FORCEINLINE SPtr<T> newSPtr() {
  return std::make_shared<T>();
}

/**
 * @brief wraper of the std::swap
 * @tparam T
 * @param a
 * @param b
*/
FORCEINLINE void swap(float& a, float& b) {
  std::swap(a, b);
}

/**
 * @brief wraper for the std::map
 * @tparam T1 
 * @tparam T2 
*/
template <class T1, class T2>
using Map = std::map<T1,T2>;

/**
 * @brief cast for smart pointers
 * @tparam T 
 * @tparam U 
 * @param pointer 
 * @return 
*/
template<class T,class U>
FORCEINLINE SPtr<T> cast(const SPtr<U>& pointer){
  return std::dynamic_pointer_cast<T>(pointer);
}

template<class T>
FORCEINLINE SPtr<T> copy(const SPtr<T>& pointer){
  return std::make_shared<T>(*pointer.get());
}


}