#include "oaMath.h"
#include<cmath>
int oaEngineSDK::test()
{
	return 7;
}
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
