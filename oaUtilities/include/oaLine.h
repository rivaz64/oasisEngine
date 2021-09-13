/**
 * @file oaLine.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief represents a tridimencional line from point A to B
*/
class OA_UTILITY_EXPORT Line
{
  Vector3f startingPoint;
  Vector3f direction;
  float lenght;
public:

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

  /**
   * @brief a line that goes from point A to point B
   * @param A 
   * @param B 
  */
  Line(Vector3f& A, Vector3f& B);
  FORCEINLINE Vector3f getStaringPoint() {
    return startingPoint;
  }

  FORCEINLINE Vector3f 
    getDirection() {
    return direction;
  }

  FORCEINLINE float 
    getLenght() {
    return lenght;
  }

  /**
   * @brief gives the point at a certain place in the line, o veing the begining and 1 the end of the line
   * @param f
   * @return
  */
  Vector3f 
    pointAt(float f);

  /**
   * @brief calculates the distance between the point p and this line
   * @param p 
   * @return 
  */
  float 
    distance(Vector3f& p);

  /**
   * @brief calculates the distance between the line l and this line
   * @param l 
   * @return 
  */
  float 
    distance(Line& l);
};
}


