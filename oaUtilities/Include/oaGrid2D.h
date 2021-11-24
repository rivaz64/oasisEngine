/**
* @file Grid2D.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/21/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector2U.h"

namespace oaEngineSDK{

template<class T>
class Grid2D
{
 public:
  
  /**
   * @brief initializes a grid of a certain size
   * @param size 
  */
  Grid2D(const Vector2U& _size){
    size = _size;
    data = new T[size.x*size.y];
  }

  ~Grid2D(){
    delete[] data;
  }

  /**
   * @brief gets the data at the location
   * @param location 
   * @return 
  */
  FORCEINLINE T
  getAt(const Vector2U& location){
    OA_ASSERT(location.x<size.x && location.y<size.y);
    return data[location.y*size.x+location.x];
  }

  /**
   * @brief sets the data at the location
   * @param location 
  */
  FORCEINLINE void
  setAt(const Vector2U& location, T value){
    OA_ASSERT(location.x<size.x && location.y<size.y);
    data[location.y*size.x+location.x] = value;
  }

  /**
   * @brief getter for the size of the grid
   * @return 
  */
  FORCEINLINE const Vector2U&
  getSize(){
    return size;
  }

 private:
  /**
   * @brief all the data of the grid
  */
  T* data;

  Vector2U size;
};

Grid2D<float>;

}


