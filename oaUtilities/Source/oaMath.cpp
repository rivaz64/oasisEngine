#include "oaMath.h"
#include<cmath>
float oaEngineSDK::Sqrt(float x)
{
    return sqrtf(x);
}

float oaEngineSDK::InvSqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;                       
	i = 0x5f3759df - (i >> 1);               
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));   
	y = y * ( threehalfs - ( x2 * y * y ) );   
	y = y * (threehalfs - (x2 * y * y));
	return y;
}

float oaEngineSDK::Cos(float x)
{
	return cos(x);
}

float oaEngineSDK::Sin(float x)
{
	return sin(x);
	
}

float OA_UTILITY_EXPORT oaEngineSDK::Tan(float x)
{
	return tan(x);
}

float OA_UTILITY_EXPORT oaEngineSDK::aCos(float x)
{
	return acos(x);
}

float OA_UTILITY_EXPORT oaEngineSDK::aSin(float x)
{
	return asin(x);
}

float OA_UTILITY_EXPORT oaEngineSDK::aTan(float x)
{
	return atan(x);
}

float OA_UTILITY_EXPORT oaEngineSDK::aTan2(float x, float y)
{
	return atan2(y,x);
}
