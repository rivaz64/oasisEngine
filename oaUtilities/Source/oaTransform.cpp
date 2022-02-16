#include "oaTransform.h"

namespace oaEngineSDK{

void Transform::calculate()
{
   m_matrix = 
      Matrix4f::translateMatrix(m_location)*
      Matrix4f::rotationMatrix(m_rotation)*
      Matrix4f::scaleMatrix(m_scale);
}

}

