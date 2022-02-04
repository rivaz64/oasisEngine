#include "oaOctavesNoise.h"
#include "oaVector2f.h"
void 
oaEngineSDK::OctavesNoise::init(SPtr<Noise2D> _noise, const Vector<float>& _amplitudes)
{
  noise = _noise;
  amplitudes = _amplitudes;
}

float
oaEngineSDK::OctavesNoise::valueAt(const Vector2f& point)
{
  float ans = 0;
  float actual = 1;
  for(float amplitud : amplitudes){
    ans += noise->valueAt(point*actual)*amplitud;
    actual*=2.f;
  }
  return ans;
}
