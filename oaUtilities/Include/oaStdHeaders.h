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

using std::vector;
using std::list;
using std::shared_ptr;
using std::map;
using std::pair;
using std::enable_shared_from_this;
using std::string;
using std::wstring;
using std::fstream;
using std::make_shared;
using std::reinterpret_pointer_cast;
using std::make_shared;
using std::cout;
using std::to_string;
using std::endl;

/**
 * @brief wraper of the std::vector, can be changed in the future
 * @tparam T
*/
template <class T>
using Vector = vector<T>;

/**
 * @brief wraper of the std::list, can be changed in the future
 * @tparam T
*/
template <class T>
using List = list<T>;

/**
 * @brief wraper of the std::string, can be changed in the future
 * @tparam T
*/
using String = string;

/**
 * @brief wraper of the std::wstring, can be changed in the future
 * @tparam T
*/
using WString = wstring;

/**
 * @brief wraper of the std stream
*/
using FStream = fstream;

/**
 * @brief wraper of the std::shared_ptr, can be changed in the future
 * @tparam T
*/
template <class T>
using SPtr = shared_ptr<T>;

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
using Map = map<T1,T2>;

/**
 * @brief wraper of the std::pair
 * @tparam T1 
 * @tparam T2 
*/
template <class T1, class T2>
using Pair = pair<T1,T2>;

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
using SharedEnabled = enable_shared_from_this<T>;

/**
 * @brief prints a string to the console
 * @param s 
*/
FORCEINLINE void
print(String s){
  cout<<s<<endl;
}

}