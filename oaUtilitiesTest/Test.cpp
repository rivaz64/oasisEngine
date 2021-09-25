#include <gtest\gtest.h>
#include "oaMath.h"
#include "oaVector2f.h"
#include "oaVector3f.h"
#include "oaVector4f.h"
#include "oaMatrix3f.h"
#include "oaMatrix4f.h"
#include "oaQuaternion.h"
#include "oaLine.h"
#include "oaPlane.h"
#include "oaSphere.h"
#include "oaBoxAABB.h"
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}
using namespace oaEngineSDK;
TEST(basic, basic_types) {
  EXPECT_EQ(1, sizeof(unsigned char));
  EXPECT_EQ(1, sizeof(uint8));
  EXPECT_EQ(2, sizeof(uint16));
  EXPECT_EQ(4, sizeof(uint32));
  EXPECT_EQ(8, sizeof(uint64));

  EXPECT_EQ(1, sizeof(char));
  EXPECT_EQ(1, sizeof(int8));
  EXPECT_EQ(2, sizeof(int16));
  EXPECT_EQ(4, sizeof(int32));
  EXPECT_EQ(8, sizeof(int64));

  EXPECT_EQ(4, sizeof(float));
  EXPECT_EQ(8, sizeof(double));
}
TEST(math, basic) {
  EXPECT_EQ(Math::sqrt(49), 7);
  EXPECT_EQ(Math::invSqrt(49), 1.f/7.f);
}
TEST(math, trigonometry) {
  EXPECT_NEAR(Math::sin(.5f), Math::fastSin(.5f), .001f);
  EXPECT_NEAR(Math::cos(.5f), Math::fastCos(.5f), .001f);
  EXPECT_NEAR(Math::tan(.5f), Math::fastTan(.5f), .001f);
  EXPECT_NEAR(Math::asin(.5f), Math::fastAsin(.5f), .001f);
  EXPECT_NEAR(Math::acos(.5f), Math::fastAcos(.5f), .001f);
  EXPECT_NEAR(Math::atan(.5f), Math::fastAtan(.5f), .001f);
}

TEST(vectors, vector2) {
  EXPECT_EQ(8, sizeof(Vector2f));
  Vector2f v2 = { 3.f,4.f }, vec2 = { 5.f,12.f };
  EXPECT_EQ(v2 + vec2, Vector2f(8.f, 16.f));
  EXPECT_EQ(vec2 - v2, Vector2f(2.f, 8.f));
  EXPECT_EQ(v2 * 7.f, Vector2f(21.f, 28.f));
  EXPECT_EQ(v2 / 2.f, Vector2f(1.5f, 2.f));
  EXPECT_EQ(Vector2f::dot(v2,vec2), 63.f);
  EXPECT_EQ(v2.magnitud(), 5.f);
  EXPECT_NEAR(v2.getDirection(), 53.1301 * Math::DEG_TO_RAD, .00001f);
  v2.x *= -1;
  EXPECT_NEAR(v2.getDirection(), 126.87 * Math::DEG_TO_RAD, .00001f);
  v2.y *= -1;
  EXPECT_NEAR(v2.getDirection(), -126.87 * Math::DEG_TO_RAD, .00001f);
  v2.x *= -1;
  EXPECT_NEAR(v2.getDirection(), -53.1301 * Math::DEG_TO_RAD, .00001f);
  v2.y *= -1;
  EXPECT_NEAR(v2.normal().magnitud(), 1.f, .00001f);
  EXPECT_NEAR(v2.normal().getDirection(), v2.getDirection(), .0000001f);
  EXPECT_NEAR(v2.project(vec2).x, 1.86391f, .00001f);
  EXPECT_NEAR(v2.project(vec2).y, 4.47337f, .00001f);
  v2.setDirection(0.6435011087932843868);
  EXPECT_NEAR(v2.x, 4.f, .0000001f);
  EXPECT_NEAR(v2.y, 3.f, .0000001f);
}

TEST(vectors, vector3) {
  EXPECT_EQ(12, sizeof(Vector3f));
  Vector3f v3 = { 1.f,1.f,2.f }, vec3 = { 2.f,3.f,6.f };
  EXPECT_EQ(v3 + vec3, Vector3f(3.f, 4.f,8.f));
  EXPECT_EQ(vec3 - v3, Vector3f(1.f, 2.f,4.f));
  EXPECT_EQ(vec3 * 7.f, Vector3f(14.f, 21.f,42.f));
  EXPECT_EQ(vec3 /2.f, Vector3f(1.f, 1.5f, 3.f));
  EXPECT_EQ(v3.dot(vec3), 17.f);
  EXPECT_EQ(vec3.len(), 7.f);
  EXPECT_NEAR(v3.normal().len(), 1.f, .0001f);
  EXPECT_EQ(v3.cross(vec3), Vector3f(0.f, -2.f, 1.f));
  EXPECT_NEAR(v3.project(vec3).x, 0.693878f, .00001f);
  EXPECT_NEAR(v3.project(vec3).y, 1.04082f, .00001f);
  EXPECT_NEAR(v3.project(vec3).z, 2.08163f, .00001f);
}

TEST(vectors, vector4) {
  EXPECT_EQ(16, sizeof(Vector4f));
  Vector4f v4 = { 1.f,2.f,3.f,4.f }, vec4 = { 3.f,4.f,12.f,84.f };
  EXPECT_EQ(v4 + vec4, Vector4f(4.f, 6.f, 15.f,88.f));
  EXPECT_EQ(vec4 - v4, Vector4f(2.f, 2.f, 9.f,80.f));
  EXPECT_EQ(vec4 * 7.f, Vector4f(21.f, 28.f, 84.f,588.f));
  EXPECT_EQ(vec4 / 2.f, Vector4f(1.5, 2.f, 6.f, 42.f));
  EXPECT_EQ(v4.dot(vec4), 383.f);
  EXPECT_EQ(vec4.len(), 85.f);
  EXPECT_NEAR(v4.normal().len(), 1.f, .0001f);
  EXPECT_NEAR(v4.project(vec4).x, 0.159031f, .00001f);
  EXPECT_NEAR(v4.project(vec4).y, 0.212042f, .00001f);
  EXPECT_NEAR(v4.project(vec4).z, 0.636125f, .00001f);
  EXPECT_NEAR(v4.project(vec4).w, 4.45287f, .00001f);
}

TEST(Matrix, Matrix3) {
  EXPECT_EQ(sizeof(Matrix3f), 36);
  Vector3f v3 = { 1.f,1.f,2.f }, vec3 = { 2.f,3.f,6.f };
  Vector2f v2 = { 3.f,4.f };
  Matrix3f m(3.f);
  EXPECT_TRUE(m == Matrix3f( 3.f,0.f,0.f ,
              0.f,3.f,0.f,
              0.f,0.f,3.f));
  Matrix3f m1 = {
    2.f,3.f,5.f,
    7.f,11.f,13.f,
    17.f,19.f,23.f
  };
  Matrix3f m2 = {
    1.f,1.f,2.f,
    3.f,5.f,8.f,
    13.f,21.f,34.f
  };
  EXPECT_EQ(m1 + m2, Matrix3f( 3.f,4.f,7.f ,
            10.f,16.f,21.f ,
            30.f,40.f,57.f ));
  EXPECT_EQ(m1 - m2, Matrix3f( 1.f,2.f,3.f ,
            4.f,6.f,5.f ,
            4.f,-2.f,-11.f ));
  EXPECT_EQ(m1 * 11.f, Matrix3f( 22.f,33.f,55.f ,
            77.f,121.f,143.f ,
            187.f,209.f,253.f ));
  EXPECT_EQ(m1 * vec3, Vector3f(43, 125, 229));
  EXPECT_EQ(m1 * m2, Matrix3f({ 76.f, 122.f, 198.f,
                                209.f, 335.f, 544.f,
                                373.f, 595.f, 968.f }));
  m1.transpose();
  EXPECT_EQ(m1, Matrix3f({ 2.f, 7.f, 17.f,
                           3.f, 11.f, 19.f,
                           5.f, 13.f, 23.f }));
  m1.transpose();
  EXPECT_EQ(m1.determinant(), -78.f);
  Matrix3f m3 = {
    1.f,2.f,3.f,
    0.f,1.f,4.f,
    5.f,6.f,0.f
  };
  EXPECT_EQ(m3.inverse(), Matrix3f({ -24.f, 18.f, 5.f,
                                20.f, -15.f, -4.f,
                                -5.f, 4.f, 1.f}));
  EXPECT_EQ(Matrix3f::translateMatrix(v2), Matrix3f({ 1.f, 0.f, 3.f,
                                                      0.f, 1.f, 4.f,
                                                      0.f, 0.f, 1.f }));
  EXPECT_EQ(Matrix3f::scaleMatrix(v2), Matrix3f({ 3.f, 0.f, 0.f,
                                                      0.f, 4.f, 0.f,
                                                      0.f, 0.f, 1.f }));
  EXPECT_NEAR(Matrix3f::rotationMatrix(Math::HALF_PI).determinant(), 1,.0001f);

}
TEST(Matrix, Matrix4) {
  EXPECT_EQ(sizeof(Matrix4f), 64);
  Vector3f vec3 = { 2.f,3.f,6.f };
  Vector4f v4 = { 1.f,2.f,3.f,4.f }, vec4 = { 3.f,4.f,12.f,84.f };
  Matrix4f m(5.f);
  EXPECT_TRUE(m == Matrix4f( 5.f,0.f,0.f,0.f ,
                             0.f,5.f,0.f,0.f ,
                             0.f,0.f,5.f,0.f ,
                             0.f,0.f,0.f,5.f ));
  Matrix4f m1 = {
    1.f,2.f,3.f,4.f,
    2.f,5.f,7.f,3.f,
    4.f,10.f,14.f,6.f,
    3.f,4.f,2.f,7.f,
  };
  Matrix4f m2 = {
    1.f,2.f,-1.f,3.f,
    2.f,1.f,-2.f,3.f,
    3.f,1.f,2.f,1.f,
    1.f,-1.f,0.f,2.f,
  };
  EXPECT_EQ(m1 + m2, Matrix4f({ 2.f,4.f,2.f,7.f,
                                4.f,6.f,5.f,6.f,
                                7.f,11.f,16.f,7.f,
                                4.f,3.f,2.f,9.f, }));
  EXPECT_EQ(m1 - m2, Matrix4f({ 0.f,0.f,4.f,1.f,
                                0.f,4.f,9.f,0.f,
                                1.f,9.f,12.f,5.f,
                                2.f,5.f,2.f,5.f, }));
  EXPECT_EQ(m1 * 7.f, Matrix4f({ 7.f,14.f,21.f,28.f,
                                 14.f,35.f,49.f,21.f,
                                 28.f,70.f,98.f,42.f,
                                 21.f,28.f,14.f,49.f, }));
  EXPECT_EQ(m1 * vec4, Vector4f(383.f, 362.f, 724.f, 637.f));
  EXPECT_EQ(m1 * m2, Matrix4f({ 18.f,3.f,1.f,20.f,
                                36.f,13.f,2.f,34.f,
                                72.f,26.f,4.f,68.f,
                                24.f,5.f,-7.f,37.f }));
  m1.transpose();
  EXPECT_EQ(m1, Matrix4f({ 1.f,2.f,4.f,3.f,
                           2.f,5.f,10.f,4.f,
                           3.f,7.f,14.f,2.f,
                           4.f,3.f,6.f,7.f, }));
  m1.transpose();
  Matrix4f m3 = {
   1.f,0.f,0.f,1.f,
   0.f,2.f,1.f,2.f,
   2.f,1.f,0.f,1.f,
   2.f,0.f,1.f,4.f,
  };
  m3.transpose();
  EXPECT_EQ(m3.inverse(), Matrix4f({ -2.f,-.5f,1.f,.5f,
                                     1.f,.5f,0.f,-.5f,
                                     -8.f,-1.f,2.f,2.f,
                                     3.f,.5f,-1.f,-.5f, }));
  EXPECT_EQ(Matrix4f::translateMatrix(vec3), Matrix4f({ 1.f, 0.f, 0.f,2.f,
                                                        0.f, 1.f, 0.f,3.f,
                                                        0.f, 0.f, 1.f,6.f,
                                                        0.f, 0.f, 0.f,1.f }));
  EXPECT_EQ(Matrix4f::scaleMatrix(vec3), Matrix4f({ 2.f, 0.f, 0.f,0.f,
                                                    0.f, 3.f, 0.f,0.f,
                                                    0.f, 0.f, 6.f,0.f,
                                                    0.f, 0.f, 0.f,1.f }));
  /*EXPECT_NEAR(Matrix4f::rotationMatrixZ(Math::pi / 4.f).determinant(), 1, .0001f);
  EXPECT_NEAR(Matrix4f::rotationMatrixX(3.f* Math::pi / 4.f).determinant(), 1, .0001f);
  EXPECT_NEAR(Matrix4f::rotationMatrixY(-Math::pi / 4.f).determinant(), 1, .0001f);*/

}
TEST(Quaternions, basic) {
  EXPECT_EQ(sizeof(Quaternion), 16);
  Quaternion q = { 1,2,3,4 },qua = q.conjugate();
  EXPECT_EQ(q * qua, Quaternion(30, 0, 0, 0));
  EXPECT_EQ(q.inverse(), Quaternion(1.f / 30.f, -1.f / 15.f, -1.f / 10.f, -2.f / 15.f));
}
TEST(geometry, line) {
  EXPECT_EQ(sizeof(Line), 28);
  Vector3f A = { 1.f,1.f,2.f }, B = { 2.f,3.f,6.f }, C = { 5.f,5.f,5.f };
  Line stick = { A,B };
  EXPECT_EQ(stick.getStaringPoint(), A);
  EXPECT_NEAR(stick.getLenght(), 4.58257f,.00001f);
  EXPECT_NEAR(stick.getDirection().x, 0.218217f, .000001f);
  EXPECT_NEAR(stick.getDirection().y, 0.436435f, .000001f);
  EXPECT_NEAR(stick.getDirection().z, 0.872871f, .000001f);
  Vector3f midpoint = stick.pointAt(.5f);
  EXPECT_NEAR(midpoint.x, 1.5f, .000001f);
  EXPECT_NEAR(midpoint.y, 2.f, .000001f);
  EXPECT_NEAR(midpoint.z, 4.f, .000001f);
  EXPECT_NEAR(stick.distance(C), 3.68394f, .00001f);
  Vector3f D = { 1.f,2.f,3.f }, E = { 2.f,3.f,5.f };
  Line l = { D,E };
  EXPECT_NEAR(stick.distance(l), 0.447214f,.000001f);
  Vector3f F = { 2.f,2.f,3.f }, G = { 3.f,4.f,7.f };
  Line parallel = { F,G };
  EXPECT_NEAR(stick.distance(parallel), 0.816497f,.00001f);
}
TEST(geometry, plane) {
  EXPECT_EQ(sizeof(Plane), 16);
  Vector3f A = { 1.f,2.f,1.f }, B = { 6.f,3.f,2.f }, C = { 2.f,3.f,5.f };
  Vector4f D = { 4.f,4.f,4.f,1.f };
  Plane paper = { A,B,C };
  EXPECT_EQ(paper.getNormal(), Vector3f(3, -19, 4).normal());
  EXPECT_NEAR(paper.getD(), 1.57785F,.00001f);
  EXPECT_NEAR(paper.distance(D.xyz), .865277, .000001f);
  Matrix4f refMat = paper.reflection();
  Vector4f refpoint = refMat * D;
  EXPECT_NEAR(refpoint.x, 4.26f, .01f);
  EXPECT_NEAR(refpoint.y, 2.33f, .01f);
  EXPECT_NEAR(refpoint.z, 4.35f, .01f);

  Line arrow = Line(D.xyz,refpoint.xyz);
  Vector3f intersection;
  EXPECT_TRUE(paper.intersect(arrow, intersection));
  EXPECT_NEAR(intersection.x, 4.13, 0.01f);
  
  Plane paper1 = { A,D.xyz,refpoint.xyz };
  Plane paper2 = { C,D.xyz,refpoint.xyz };
  Line cut;
  paper.intersect(paper1,paper2, intersection);
  EXPECT_EQ(intersection, arrow.pointAt(.5));
}

TEST(overlaps, shpere) {
  Sphere ball({ 2,3,6 }, 4);
  Vector3f A = { 1.f,1.f,7.f };
  Vector3f B = { 7.f,8.f,9.f };
  EXPECT_TRUE(ball.isInside(A));
  EXPECT_FALSE(ball.isInside(B));
  EXPECT_TRUE(ball.overlap(Sphere(A, 1)));
  EXPECT_FALSE(ball.overlap(Sphere(B, 1)));
  EXPECT_TRUE(ball.overlap(Sphere(B, 5)));
}

TEST(overlaps, AABBbox) {
  BoxAABB box = BoxAABB({ 1.f,3.f,5.f }, { 6.f,4.f,2.f });
  EXPECT_TRUE(box.isPointInside({ 3.f,3.5f,4.f }));
  EXPECT_FALSE(box.isPointInside({ 0.f,3.5f,4.f }));
  EXPECT_TRUE(box.overlap(Sphere({ 3.f,3.5f,4.f }, 12.f)));
  EXPECT_TRUE(box.overlap(Sphere({ 3.f,3.5f,4.f }, .1f)));
  EXPECT_TRUE(box.overlap(Sphere({ 0.f,3.5f,4.f }, 7.f)));
  EXPECT_FALSE(box.overlap(Sphere({ 0.f,3.5f,4.f }, .5f)));
}
