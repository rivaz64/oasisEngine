/**
 * @file oaMatrix3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include"oaPrerequisitesUtilities.h"

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
   * @param _m11 
   * @param _m12 
   * @param _m13 
   * @param _m21 
   * @param _m22 
   * @param _m23 
   * @param _m31 
   * @param _m32 
   * @param _m33 
  */
  Matrix3f(float _m11, float _m12, float _m13,
           float _m21, float _m22, float _m23,
           float _m31, float _m32, float _m33) :
    m11(_m11), m12(_m12), m13(_m13),
    m21(_m21), m22(_m22), m23(_m23),
    m31(_m31), m32(_m32), m33(_m33) {}

  ~Matrix3f() = default;

  /**
   * @brief constructor for an identity matrix
   * @param f the idnetity matrix is going to be multiplied by f
  */
  Matrix3f(float f):
    m11(f), m12(0), m13(0),
    m21(0), m22(f), m23(0),
    m31(0), m32(0), m33(f) {}

  /**
   * @brief compares if two matrix 3x3 are equal
   * @param m 
   * @return 
  */
  bool 
  operator==(const Matrix3f& m);

  /**
   * @brief adds the matrix m and this one
   * @param m
   * @return
  */
  Matrix3f
  operator+(const Matrix3f& m);

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
  operator-(const Matrix3f& m);

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
  operator*(float m);

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
  operator*(const Vector3f& v);

  /**
   * @brief the multiplication of this matrix and the matrix m
   * @param v
   * @return
  */
  Matrix3f
  operator*(const Matrix3f& m);

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
  determinant();

  /**
   * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
   * @return
  */
  Matrix3f
  inverse();

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
  /**
   * @brief value at column 1 row 1
  */
  float m11;

  /**
   * @brief value at column 2 row 1
  */
  float m12;

  /**
   * @brief value at column 3 row 1
  */
  float m13;

  /**
   * @brief value at column 1 row 2
  */
  float m21;

  /**
   * @brief value at column 2 row 2
  */
  float m22;

  /**
   * @brief value at column 3 row 2
  */
  float m23;

  /**
   * @brief value at column 1 row 3
  */
  float m31;

  /**
   * @brief value at column 2 row 3
  */
  float m32;

  /**
   * @brief value at column 3 row 3
  */
  float m33;

};

}


