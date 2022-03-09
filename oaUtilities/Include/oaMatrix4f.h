/**
 * @file oaMatrix4f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector4f.h"

namespace oaEngineSDK {
/**
 * @brief Matrix 4x4 of floats
*/
class OA_UTILITY_EXPORT Matrix4f
{
 public:
  /**
   * @brief default constructor for the Matrix4f
  */
  Matrix4f() = default;

  /**
   * @brief parametrized constructor for the Matrix4f
   * @param r1 
   * @param r2 
   * @param r3 
   * @param r4
  */
  Matrix4f(Vector4f r1, Vector4f r2, Vector4f r3, Vector4f r4) :
    row1(r1), row2(r2), row3(r3), row4(r4) {}

  /**
   * @brief constructor from a matrix3
   * @param m 
  */
  Matrix4f(const Matrix3f& m);

  ~Matrix4f() = default;

  /**
   * @brief compares if two matrix 4x4 are equal
   * @param m 
   * @return 
  */
  bool const
  operator==(const Matrix4f& m) const;

  /**
  * @brief adds the matrix m and this one
  * @param m
  * @return
 */
  Matrix4f
  operator+(const Matrix4f& m) const;

  /**
   * @brief adds the matrix m to this one
   * @param m
  */
  Matrix4f&
  operator+=(const Matrix4f& m);

  /**
   * @brief this matrix minus m
   * @param m
   * @return
  */
  Matrix4f
  operator-(const Matrix4f& m) const;

  /**
   * @brief subtracts m from this matrix
   * @param m
  */
  Matrix4f&
  operator-=(const Matrix4f& m);

  /**
   * @brief the multiplication of this matrix times m
   * @param m
   * @return
  */

  Matrix4f
  operator*(float m) const;
  /**
   * @brief multiplies this matrix times m
   * @param m
  */
  Matrix4f&
  operator*=(float m);

  /**
   * @brief the multiplication of this matrix and the vector v
   * @param v
   * @return
  */
  Vector4f
  operator*(const Vector4f& v) const;

  /**
   * @brief the multiplication of this matrix and the matrix m
   * @param v
   * @return
  */
  Matrix4f
  operator*(const Matrix4f& m) const;

  /**
   * @brief multiplies this matrix times the matrix m
   * @param m
  */
  Matrix4f&
  operator*=(const Matrix4f& m);

  /**
   * @brief returns the xyz elementts of the firts 3 rows
   * @return 
  */
  Matrix3f
  toMatrix3f() const;

  /**
   * @brief changes the rows for the columns
  */
  void
  transpose();

  /**
   * @brief changes the rows for the columns
  */
  Matrix4f
  transposed() const;

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
  Matrix4f
  inverse() const;

  /**
  * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
  * @return
  */
  void
  invert();

  /**
   * @brief creates a translate matrix for the given position
  */
  static Matrix4f 
  translateMatrix(const Vector3f& v);

  /**
   * @brief creates a scale matrix for the given size
  */
  static Matrix4f 
  scaleMatrix(const Vector3f& v);

  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the Z axis
  */
  static Matrix4f
  rotationMatrixZ(const float r);

  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the X axis
  */
  static Matrix4f
  rotationMatrixX(const float r);

  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the Y axis
  */
  static Matrix4f
  rotationMatrixY(const float r);

  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the arbitrary axis v
  */
  static Matrix4f
  rotationMatrix(float r,const Vector3f& v);

  /**
   * @brief the rotation matrix
   * @param v the rotation aplied in each axis
   * @return 
  */
  static Matrix4f
  rotationMatrix(const Vector3f& v);
  
 public:

  Vector4f row1;

  Vector4f row2;

  Vector4f row3;

  Vector4f row4;

   static const Matrix4f IDENTITY;
};

}