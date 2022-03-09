/**
 * @file oaMatrix3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {
/**
 * @brief Matrix 3x3 of floats
*/
class OA_UTILITY_EXPORT Matrix3f
{
 public:

  /**
   * @brief default constructor for the Matrix3f
  */
  Matrix3f() = default;

  /**
   * @brief parametrized constructor for the Matrix3f
   * @param r1 
   * @param r2 
   * @param r3 
  */
  Matrix3f(Vector3f r1, Vector3f r2, Vector3f r3) :
    row1(r1), row2(r2), row3(r3) {}

  ~Matrix3f() = default;

  /**
   * @brief compares if two matrix 3x3 are equal
   * @param m 
   * @return 
  */
  bool const
  operator==(const Matrix3f& m) const;

  /**
   * @brief adds the matrix m and this one
   * @param m
   * @return
  */
  Matrix3f 
  operator+(const Matrix3f& m) const;

  /**
   * @brief adds the matrix m to this one
   * @param m
  */
  Matrix3f&
  operator+=(const Matrix3f& m);

  /**
   * @brief this matrix minus m
   * @param m
   * @return
  */
  Matrix3f
  operator-(const Matrix3f& m) const;

  /**
   * @brief subtracts m from this matrix
   * @param m
  */
  Matrix3f&
  operator-=(const Matrix3f& m);

  /**
   * @brief the multiplication of this matrix times m
   * @param m
   * @return
  */
  Matrix3f
  operator*(float m) const;

  /**
   * @brief multiplies this matrix times m
   * @param m
  */
  Matrix3f&
  operator*=(float m);

  /**
   * @brief the multiplication of this matrix and the vector v
   * @param v
   * @return
  */
  Vector3f
  operator*(const Vector3f& v) const;

  /**
   * @brief the multiplication of this matrix and the matrix m
   * @param v
   * @return
  */
  Matrix3f
  operator*(const Matrix3f& m) const;

  /**
   * @brief multiplies this matrix times the matrix m
   * @param m
  */
  Matrix3f&
  operator*=(const Matrix3f& m);

  /**
   * @brief changes the rows for the columns
  */
  void
  transpose();

  /**
   * @brief calculates the determinant of the matrix
   * @return
  */
  float
  determinant() const;

  /**
   * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
   * @return
  */
  Matrix3f
  inverse() const;

  /**
  * @brief inverts this matrix
  * @return
  */
  void
  invert();

  FORCEINLINE const void*
  getData(){
    return &row1.x;
  }

  /**
   * @brief creates a translate matrix for the given position
  */
  static Matrix3f
  translateMatrix(const Vector2f& v);

  /**
   * @brief creates a scale matrix for the given size
  */
  static Matrix3f
  scaleMatrix(const Vector2f& v);

  /**
   * @brief creates a rotation matrix for the given angle r in radians
  */
  static Matrix3f
  rotationMatrix(float r);

 public:
  
  Vector3f row1;

  Vector3f row2;

  Vector3f row3;

};

}


