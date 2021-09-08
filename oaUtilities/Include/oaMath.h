/**
 * @file oaMath.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */
#pragma once
#include "oaPlatformDefines.h"
namespace oaEngineSDK {
const float pi = 3.1415926535897932384626433832795f;
const float radiansToDegrees = 180.f / pi;
const float degreesToRadians = pi / 180.f;
/**
 * @brief wraper of the cmath sqrt
 * @param x 
 * @return 
*/
float OA_UTILITY_EXPORT Sqrt(float x);
/**
 * @brief the infamous Q_rsqrt by sir John Karmak
 * @param number 
 * @return 1/sqrt(x)d
*/
float OA_UTILITY_EXPORT InvSqrt(float number);
/**
 * @brief wraper of the cmath cos
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT Cos(float x);
/**
 * @brief wraper of the cmath sin
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT Sin(float x);
/**
 * @brief wraper of the cmath tan
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT Tan(float x);
/**
 * @brief wraper of the cmath acos
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT aCos(float x);
/**
 * @brief wraper of the cmath asin
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT aSin(float x);
/**
 * @brief wraper of the cmath atan
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT aTan(float x);
/**
 * @brief wraper of the cmath atan2
 * @param x
 * @return
*/
float OA_UTILITY_EXPORT aTan2(float x,float y);

}