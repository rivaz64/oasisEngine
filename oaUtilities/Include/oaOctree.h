/**
* @file oaTriangle.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/23/2022
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"
#include "oaPlane.h"


namespace oaEngineSDK{

/**
 * @brief a node for the octTree
*/
struct OA_UTILITY_EXPORT OctreeNode{
  /**
   * @brief  the subdivisions of this node of the octree
  */
  SPtr<OctreeNode> childs[8];

  /**
   * @brief the location of the center
  */
  Vector3f location;

  /**
   * @brief the size of a edge of the node
  */
  float size;
};

/**
 * @brief an octree 
*/
class OA_UTILITY_EXPORT Octree
{
 public:

  Octree(const Vector3f& center) :
   m_center(center){}
  /**
   * @brief gets the planes that divides the cube of the root
   * @return 
  */
  Vector<Plane> 
  getPlanes();

  Vector<Vector3f> 
  getCenters(float size);

 private:
  
  /**
   * @brief this is the cube of the total area
  */
  SPtr<OctreeNode> m_root;

  Vector3f m_center;
};

}


