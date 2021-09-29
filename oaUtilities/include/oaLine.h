/**
 * @file oaLine.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {
/**
 * @brief represents a tridimencional line from point A to B
*/
class OA_UTILITY_EXPORT Line
{
 public:
  /**
   * @brief default constructor for the Line
  */
  Line() = default;

  /**
   * @brief gives directly the variables needed for a line
   * @param sp 
   * @param d 
   * @param l 
  */
  Line(const Vector3f& _startingPoint, const Vector3f& _direction, float _lenght) :
    startingPoint(_startingPoint),
    direction(_direction),
    lenght(_lenght) {}

  ~Line() = default;
  /**
   * @brief a line that goes from point A to point B
   * @param A 
   * @param B 
  */
  Line(Vector3f& A, Vector3f& B);

  /**
   * @brief getter for the starting point
   * @return 
  */
  FORCEINLINE const Vector3f&
  getStaringPoint() const {
    return startingPoint;
  }

  /**
   * @brief getter for the direction
   * @return 
  */
  FORCEINLINE const Vector3f&
  getDirection() const {
    return direction;
  }

  /**
   * @brief getter for the lenght
   * @return 
  */
  FORCEINLINE float 
  getLenght() {
    return lenght;
  }

  /**
   * @brief setter for the starting point
   * @param _startingPoint 
  */
  FORCEINLINE void 
  setStaringPoint(const Vector3f& _startingPoint) {
    startingPoint = _startingPoint;
  }

  /**
   * @brief setter for the direction
   * @param _direction 
  */
  FORCEINLINE void
  setDirection(const Vector3f& _direction) {
    direction = _direction.normalized();
  }

  /**
   * @brief setter for the lenght
   * @param _lenght 
  */
  FORCEINLINE void
  setLenght(float _lenght) {
    lenght = _lenght;
  }

  /**
   * @brief gives the point at a certain place in the line, o veing the begining and 1 the end of the line
   * @param f
   * @return
  */
  Vector3f 
  pointAt(float f);

 private:
   /**
    * @brief the point where the line starts
   */
   Vector3f startingPoint;
   /**
    * @brief the direction where the line goes 
   */
   Vector3f direction;
   /**
    * @brief the lenght of the line
   */
   float lenght;

   friend class PlatformMath;
};
}


