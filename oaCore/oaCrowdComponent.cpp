#include "oaCrowdComponent.h"
#include "oaCrowdSim.h"
namespace oaEngineSDK
{

void 
CrowdComponent::calcPoints()
{
  auto& cs = CrowdSim::instance();
  m_points = cs.scatter(m_numOfPoints,m_minPoint,m_maxPoint,m_radii,m_iterations,749);
}

}

