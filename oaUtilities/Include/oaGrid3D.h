/**
* @file Grid3D.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/21/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3I.h"

namespace oaEngineSDK{

template<class T>
class Grid3D
{
 public:
  
  /**
   * @brief initializes a grid of a certain size
   * @param size 
  */
  Grid3D(const Vector3U& _size){
    size = _size;
    data = new T[size.x*size.y*size.z];
  }

  ~Grid3D(){
    delete[] data;
  }

  /**
   * @brief gets the data at the location
   * @param location 
   * @return 
  */
  FORCEINLINE T
  getAt(const Vector3U& location) const {
    OA_ASSERT(location.x<size.x && location.y<size.y && location.z<size.z);
    return data[location.z*size.y*size.x+location.y*size.x+location.x];
  }

  /**
   * @brief sets the data at the location
   * @param location 
  */
  FORCEINLINE void
  setAt(const Vector3U location, T value){
    OA_ASSERT(location.x<size.x && location.y<size.y && location.z<size.z);
    data[location.z*size.y*size.x+location.y*size.x+location.x] = value;
  }

  /**
   * @brief getter for the size of the grid
   * @return 
  */
  FORCEINLINE const Vector3U&
  getSize() const{
    return size;
  }

  /**
   * @brief checks if a position is in the grid
   * @tparam T 
  */
  FORCEINLINE bool
  isIn(const Vector3I& location) const{
    return location.x>=0 && location.x<size.x &&
           location.y>=0 && location.y<size.y &&
           location.z>=0 && location.z<size.z;
  }

 private:
  /**
   * @brief all the data of the grid
  */
  T* data;

  Vector3U size;
};

//Grid3D<bool>;
//Grid3D<float>;

}
