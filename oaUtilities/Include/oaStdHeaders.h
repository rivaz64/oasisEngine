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
#include <iostream>
#include <fstream>

namespace oaEngineSDK {

using std::make_shared;
using std::reinterpret_pointer_cast;
using std::make_shared;
using std::cout;
using std::to_string;

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
 * @brief wraper of the std stream
*/
using FStream = std::fstream;

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
FORCEINLINE SPtr<T> 
newSPtr() {
  return make_shared<T>();
}

/**
 * @brief wraper of the std::swap
 * @tparam T
 * @param a
 * @param b
*/
FORCEINLINE void 
swap(float& a, float& b) {
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
 * @brief wraper of the std::pair
 * @tparam T1 
 * @tparam T2 
*/
template <class T1, class T2>
using Pair = std::pair<T1,T2>;

/**
 * @brief cast for smart pointers
 * @tparam T 
 * @tparam U 
 * @param pointer 
 * @return 
*/
template<class T,class U>
FORCEINLINE SPtr<T> 
cast(const SPtr<U>& pointer){
  return reinterpret_pointer_cast<T>(pointer);
}

template<class T>
FORCEINLINE SPtr<T> 
copy(const SPtr<T>& pointer){
  return make_shared<T>(*pointer.get());
}

/**
 * @brief wraper for a class that can make a shared from this
*/
template<class T>
using SharedEnabled = std::enable_shared_from_this<T>;

/**
 * @brief prints a string to the console
 * @param s 
*/
FORCEINLINE void
print(String s){
  std::cout<<s<<std::endl;
}

/**
 * @brief changes something to string
 * @tparam T the tipe of the argument
 * @param param the thig to be converted to string
 * @return the string
*/
template<class T>
FORCEINLINE String
toString(T param){
  return to_string(param);
}




}