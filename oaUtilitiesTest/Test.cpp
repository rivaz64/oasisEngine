#include<gtest\gtest.h>
#include"../oaUtilities/Include/oaMath.h"
#include"../oaUtilities/Include/oaVector2f.h"
#include"../oaUtilities/Include/oaVector3f.h"
#include"../oaUtilities/Include/oaVector4f.h"
#include"../oaUtilities/Include/oaMatrix3f.h"
#include"../oaUtilities/Include/oaMatrix4f.h"
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
  EXPECT_EQ(Sqrt(49), 7);
  EXPECT_EQ(InvSqrt(49), 1.f/7.f);
}
TEST(vectors, vector2) {
  EXPECT_EQ(8, sizeof(Vector2f));
  Vector2f v2 = { 3.f,4.f }, vec2 = { 5.f,12.f };
  EXPECT_EQ(v2 + vec2, Vector2f(8.f, 16.f));
  EXPECT_EQ(vec2 - v2, Vector2f(2.f, 8.f));
  EXPECT_EQ(v2 * 7.f, Vector2f(21.f, 28.f));
  EXPECT_EQ(v2 / 2.f, Vector2f(1.5f, 2.f));
  EXPECT_EQ(v2.dot(vec2), 63.f);
  EXPECT_EQ(v2.len(), 5.f);
  EXPECT_NEAR(v2.normal().len(), 1.f, .00001f);
  EXPECT_NEAR(v2.project(vec2).x, 1.86391f, .00001f);
  EXPECT_NEAR(v2.project(vec2).y, 4.47337f, .00001f);
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
  Matrix3f m(3.f);
  EXPECT_TRUE(m == Matrix3f({ 3.f,0.f,0.f },
              { 0.f,3.f,0.f },
              { 0.f,0.f,3.f }));
  Matrix3f m1 = {
    {2.f,3.f,5.f},
    {7.f,11.f,13.f},
    {17.f,19.f,23.f}
  };
  Matrix3f m2 = {
    {1.f,1.f,2.f},
    {3.f,5.f,8.f},
    {13.f,21.f,34.f}
  };
  EXPECT_EQ(m1 + m2, Matrix3f({ 3.f,4.f,7.f },
            { 10.f,16.f,21.f },
            { 30.f,40.f,57.f }));
  EXPECT_EQ(m1 - m2, Matrix3f({ 1.f,2.f,3.f },
            { 4.f,6.f,5.f },
            { 4.f,-2.f,-11.f }));
  EXPECT_EQ(m1 * 11.f, Matrix3f({ 22.f,33.f,55.f },
            { 77.f,121.f,143.f },
            { 187.f,209.f,253.f }));
  EXPECT_EQ(m1 * vec3, Vector3f(43, 125, 229));
  EXPECT_EQ(m1 * m2, Matrix3f({ {76.f, 122.f, 198.f},
                                {209.f, 335.f, 544.f},
                                {373.f, 595.f, 968.f} }));
  m1.transpose();
  EXPECT_EQ(m1, Matrix3f({ {2.f, 7.f, 17.f},
                           {3.f, 11.f, 19.f},
                           {5.f, 13.f, 23.f} }));
  m1.transpose();
  EXPECT_EQ(m1.determinant(), -78.f);
  Matrix3f m3 = {
    {1.f,2.f,3.f},
    {0.f,1.f,4.f},
    {5.f,6.f,0.f}
  };
  EXPECT_EQ(m3.inverse(), Matrix3f({ {-24.f, 18.f, 5.f},
                                {20.f, -15.f, -4.f},
                                {-5.f, 4.f, 1.f} }));

}
TEST(Matrix, Matrix4) {
  EXPECT_EQ(sizeof(Matrix4f), 64);
  Vector4f v4 = { 1.f,2.f,3.f,4.f }, vec4 = { 3.f,4.f,12.f,84.f };
  Matrix4f m(5.f);
  EXPECT_TRUE(m == Matrix4f({ 5.f,0.f,0.f,0.f },
                            { 0.f,5.f,0.f,0.f },
                            { 0.f,0.f,5.f,0.f },
                            { 0.f,0.f,0.f,5.f }));
  Matrix4f m1 = {
    {1.f,2.f,3.f,4.f},
    {2.f,5.f,7.f,3.f},
    {4.f,10.f,14.f,6.f},
    {3.f,4.f,2.f,7.f},
  };
  Matrix4f m2 = {
    {1.f,2.f,-1.f,3.f},
    {2.f,1.f,-2.f,3.f},
    {3.f,1.f,2.f,1.f},
    {1.f,-1.f,0.f,2.f},
  };
  EXPECT_EQ(m1 + m2, Matrix4f({ {2.f,4.f,2.f,7.f},
                                {4.f,6.f,5.f,6.f},
                                {7.f,11.f,16.f,7.f},
                                {4.f,3.f,2.f,9.f}, }));
  EXPECT_EQ(m1 - m2, Matrix4f({ {0.f,0.f,4.f,1.f},
                                {0.f,4.f,9.f,0.f},
                                {1.f,9.f,12.f,5.f},
                                {2.f,5.f,2.f,5.f}, }));
  EXPECT_EQ(m1 * 7.f, Matrix4f({ {7.f,14.f,21.f,28.f},
                                 {14.f,35.f,49.f,21.f},
                                 {28.f,70.f,98.f,42.f},
                                 {21.f,28.f,14.f,49.f}, }));
  EXPECT_EQ(m1 * vec4, Vector4f(383.f, 362.f, 724.f, 637.f));
  EXPECT_EQ(m1 * m2, Matrix4f({ {18.f,3.f,1.f,20.f},
                                {36.f,13.f,2.f,34.f},
                                {72.f,26.f,4.f,68.f},
                                {24.f,5.f,-7.f,37.f}, }));
  m1.transpose();
  EXPECT_EQ(m1, Matrix4f({ {1.f,2.f,4.f,3.f},
                           {2.f,5.f,10.f,4.f},
                           {3.f,7.f,14.f,2.f},
                           {4.f,3.f,6.f,7.f}, }));
  Matrix4f m3 = {
   {1.f,0.f,0.f,1.f},
   {0.f,2.f,1.f,2.f},
   {2.f,1.f,0.f,1.f},
   {2.f,0.f,1.f,4.f},
  };
  EXPECT_EQ(m3.inverse(), Matrix4f({ {-2.f,-.5f,1.f,.5f},
                                     {1.f,.5f,0.f,-.5f},
                                     {-8.f,-1.f,2.f,2.f},
                                     {3.f,.5f,-1.f,-.5f}, }));

}