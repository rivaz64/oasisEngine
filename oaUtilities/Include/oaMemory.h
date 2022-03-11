/**
 * @file oaMemory.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 3/09/2021
 */

#pragma once

#include "oaStdHeaders.h"

namespace oaEngineSDK{

/**
* @brief wraper of the std::make_shared
* @tparam T
*/
template <typename T, typename... _Types>
FORCEINLINE SPtr<T> 
makeSPtr(_Types&&... _Args) {
  return make_shared<T>(std::forward<_Types>(_Args)...);
}

/**
 * @brief makes a const pointer a normal pointer to be filled
 * @tparam T 
 * @param pointer 
 * @return 
*/
template <typename T>
FORCEINLINE T* 
unconstPointer(const T* pointer){
  return reinterpret_cast<T*>(reinterpret_cast<SIZE_T>(pointer));
}

}
