#pragma once
#include "oaPlatformDefines.h"
namespace oaEngineSDK {
int OA_UTILITY_EXPORT test();
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
}