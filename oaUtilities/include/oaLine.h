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
   * @brief a line that goes from point A to point B
   * @param A 
   * @param B 
  */
  Line(const Vector3f& startingPoint, const Vector3f& endpoint) :
    m_startingPoint(startingPoint), m_endpoint(endpoint) {}

  ~Line() = default;

  /**
   * @brief getter for the starting point
   * @return 
  */
  FORCEINLINE const Vector3f&
  getStaringPoint() const {
    return m_startingPoint;
  }

  /**
   * @brief getter for the direction
   * @return 
  */
  FORCEINLINE Vector3f
  getDirection() const {
    return (m_endpoint-m_startingPoint).normalized();
  }
  
  ///**
  // * @brief getter for the lenght
  // * @return 
  //*/
  //FORCEINLINE float 
  //getLenght() {
  //  return lenght;
  //}

  /**
   * @brief setter for the starting point
   * @param startingPoint 
  */
  //FORCEINLINE void 
  //setStaringPoint(const Vector3f& startingPoint) {
  //  startingPoint = startingPoint;
  //}
  //
  ///**
  // * @brief setter for the direction
  // * @param _direction 
  //*/
  //FORCEINLINE void
  //setDirection(const Vector3f& _direction) {
  //  direction = _direction.normalized();
  //}
  //
  ///**
  // * @brief setter for the lenght
  // * @param _lenght 
  //*/
  //FORCEINLINE void
  //setLenght(float _lenght) {
  //  lenght = _lenght;
  //}

  /**
   * @brief gives the point at a certain place in the line, o veing the begining and 1 the end of the line
   * @param f
   * @return
  */
  //Vector3f 
  //pointAt(float f);

 private:
   /**
    * @brief the point where the line starts
   */
   Vector3f m_startingPoint;

   /**
    * @brief the point where the line ends
   */
   Vector3f m_endpoint;

   friend class PlatformMath;
};
}


