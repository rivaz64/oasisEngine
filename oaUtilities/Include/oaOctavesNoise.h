#pragma once

#include "oaNoise2D.h"

namespace oaEngineSDK{

/**
 * @brief noise with various octaves
*/
class OA_UTILITY_EXPORT OctavesNoise :
  public Noise2D
{
 public:

  /**
   * @brief 
   * @param _noise the type of noise to use in each octave
   * @param _amplitudes the list of amplitud to use in each octave
  */
  void 
  init(SPtr<Noise2D> _noise, const Vector<float>& _amplitudes);

  /**
   * @brief the value of the octaves noise at a certain point
   * @param point 
   * @return 
  */
  float 
  valueAt(const Vector2f& point) override;

 private:
  SPtr<Noise2D> noise;

  Vector<float> amplitudes;
};

}


