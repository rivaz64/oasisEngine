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
  union {
    float data[16];
    struct {
      /**
       * @brief the first row of the matrix
      */
      Vector4f a;
      /**
       * @brief the second row of the matrix
      */
      Vector4f b;
      /**
       * @brief the third row of the matrix
      */
      Vector4f c;
      /**
       * @brief the fourth row of the matrix
      */
      Vector4f d;
    };
  };
  Matrix4f() = default;
  Matrix4f(const Vector4f& _a, 
           const Vector4f& _b, 
           const Vector4f& _c, 
           const Vector4f& _d) 
    :a(_a), b(_b), c(_c), d(_d) {}
  ~Matrix4f() = default;
  /**
   * @brief constructor for an identity matrix
   * @param f the idnetity matrix is going to be multiplied by f
  */
  Matrix4f(float f);
  Vector4f& 
    operator[](uint8 i);
  /**
  * @brief adds the matrix m and this one
  * @param m
  * @return
 */
  Matrix4f 
    operator+(Matrix4f& m);
  /**
   * @brief adds the matrix m to this one
   * @param m
  */
  void 
    operator+=(Matrix4f& m);
  /**
   * @brief this matrix minus m
   * @param m
   * @return
  */
  Matrix4f
    operator-(Matrix4f& m);
  /**
   * @brief subtracts m from this matrix
   * @param m
  */
  void operator-=(Matrix4f& m);
  /**
   * @brief the multiplication of this matrix times m
   * @param m
   * @return
  */
  Matrix4f
    operator*(float m);
  /**
   * @brief multiplies this matrix times m
   * @param m
  */
  void 
    operator*=(float m);
  /**
   * @brief the multiplication of this matrix and the vector v
   * @param v
   * @return
  */
  Vector4f
    operator*(Vector4f& v);
  /**
   * @brief the multiplication of this matrix and the matrix m
   * @param v
   * @return
  */
  Matrix4f
    operator*(Matrix4f& m);
  /**
   * @brief multiplies this matrix times the matrix m
   * @param m
  */
  void 
    operator*=(Matrix4f& m);
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
private:
  /**
   * @brief calculates the determinant of a minor matrix that is in the rows and colums
   * @param r1 first row of the minor matrix
   * @param r2 second row of the minor matrix
   * @param r3 third row of the minor matrix
   * @param c1 first column of the minor matrix
   * @param c2 second column of the minor matrix
   * @param c3 third column of the minor matrix
   * @return
  */
  float 
    minorDet(uint8 r1, uint8 r2, uint8 r3, uint8 c1, uint8 c2, uint8 c3);
public:
  /**
   * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
   * @return
  */
  Matrix4f 
    inverse();
  /**
   * @brief creates a translate matrix for the given position
  */
  static Matrix4f 
    translateMatrix(Vector3f& v);
  /**
   * @brief creates a scale matrix for the given size
  */
  static Matrix4f 
    scaleMatrix(Vector3f& v);
  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the Z axis
  */
  static Matrix4f
    rotationMatrixZ(float r);
  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the X axis
  */
  static Matrix4f
    rotationMatrixX(float r);
  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the Y axis
  */
  static Matrix4f
    rotationMatrixY(float r);
  /**
   * @brief creates a rotation matrix for the given angle r in radians rotating in the arbitrary axis v
  */
  static Matrix4f
    rotationMatrix(float r, Vector3f& v);
  /**
   * @brief creates a rotation matrix for the given the quaternion q
  */
  

};
bool OA_UTILITY_EXPORT operator==(Matrix4f m1, Matrix4f m2);
}