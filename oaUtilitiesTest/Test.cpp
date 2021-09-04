#include<gtest\gtest.h>
#include"../oaUtilities/Include/oaMath.h"
#include"../oaUtilities/Include/oaVector2f.h"
//#include"../oaUtilities/Include/oaMatrix.h"
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
  EXPECT_EQ(v2+vec2,Vector2f(8.f,16.f));
  EXPECT_EQ(vec2 - v2, Vector2f(2.f, 8.f));
  EXPECT_EQ(v2 * 7.f, Vector2f(21.f, 28.f));
  EXPECT_EQ(v2.dot(vec2), 63.f);
  EXPECT_EQ(v2.len(),5.f);
  EXPECT_NEAR(v2.normal().len(),1.f,.0001f);
}
/*TEST(vectors, vector3) {
  EXPECT_EQ(12, sizeof(Vector3f));
  Vector3f v3 = { 1.f,1.f,2.f }, vec3 = { 2.f,3.f,6.f };
  EXPECT_TRUE(v3 != vec3);
  EXPECT_EQ(v3 + vec3, Vector3f(3.f, 4.f,8.f));
  EXPECT_EQ(vec3 - v3, Vector3f(1.f, 2.f,4.f));
  EXPECT_EQ(vec3 * 7.f, Vector3f(14.f, 21.f,42.f));
  EXPECT_EQ(dot(v3, vec3), 17.f);
  EXPECT_EQ(lenght(vec3), 7.f);
  EXPECT_NEAR(lenght(normalize(vec3)), 1.f, .0001f);
}
TEST(vectors, vector4) {
  EXPECT_EQ(16, sizeof(Vector4f));
  Vector4f v4 = { 1.f,2.f,3.f,4.f }, vec4 = { 3.f,4.f,12.f,84.f };
  EXPECT_TRUE(v4 != vec4);
  EXPECT_EQ(v4 + vec4, Vector4f(4.f, 6.f, 15.f,88.f));
  EXPECT_EQ(vec4 - v4, Vector4f(2.f, 2.f, 9.f,80.f));
  EXPECT_EQ(vec4 * 7.f, Vector4f(21.f, 28.f, 84.f,588.f));
  EXPECT_EQ(dot(v4, vec4), 383.f);
  EXPECT_EQ(lenght(vec4), 85.f);
  EXPECT_NEAR(lenght(normalize(vec4)), 1.f, .0001f);
}

/*TEST(Matrix, basic) {
  Matrix2f m2 = { {1.f,2.f},{3.f,4.f} };
  EXPECT_TRUE(m2==m2);
}
TEST(Matrix, Matrix3) {
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
  EXPECT_EQ(m1+m2, Matrix3f({ 3.f,4.f,7.f },
                            { 10.f,16.f,21.f },
                            { 30.f,40.f,57.f }));
}
TEST(Matrix, Matrix4) {
  Matrix4f m(5.f);
  EXPECT_TRUE(m == Matrix4f({ 5.f,0.f,0.f,0.f },
                            { 0.f,5.f,0.f,0.f },
                            { 0.f,0.f,5.f,0.f },
                            { 0.f,0.f,0.f,5.f }));
}*/