/**
 * @file oaMatrix4f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include"oaPrerequisitesUtilities.h"


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
   * @param _a
   * @param _b
   * @param _c
   * @param _d
  */
  Matrix4f(float _m11, float _m12, float _m13, float _m14,
           float _m21, float _m22, float _m23, float _m24,
           float _m31, float _m32, float _m33, float _m34,
           float _m41, float _m42, float _m43, float _m44 ) :
    m11(_m11), m12(_m12), m13(_m13), m14(_m14),
    m21(_m21), m22(_m22), m23(_m23), m24(_m24),
    m31(_m31), m32(_m32), m33(_m33), m34(_m34),
    m41(_m41), m42(_m42), m43(_m43), m44(_m44) {}

  ~Matrix4f() = default;

  /**
   * @brief compares if two matrix 4x4 are equal
   * @param m 
   * @return 
  */
  bool const
  operator==(const Matrix4f& m) const;

  /**
   * @brief constructor for an identity matrix
   * @param f the idnetity matrix is going to be multiplied by f
  */
  Matrix4f(float f):
    m11(f), m12(0), m13(0), m14(0),
    m21(0), m22(f), m23(0), m24(0),
    m31(0), m32(0), m33(f), m34(0),
    m41(0), m42(0), m43(0), m44(f) {}

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
    * @brief value at column 4 row 1
   */
   float m14;
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
    * @brief value at column 4 row 2
   */
   float m24;

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

   /**
    * @brief value at column 4 row 3
   */
   float m34;

   /**
    * @brief value at column 1 row 4
   */
   float m41;

   /**
    * @brief value at column 2 row 4
   */
   float m42;

   /**
    * @brief value at column 3 row 4
   */
   float m43;

   /**
    * @brief value at column 4 row 4
   */
   float m44;

   static const Matrix4f IDENTITY;
};

}