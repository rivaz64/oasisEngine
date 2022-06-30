#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{

/**
 * @brief a graph that a seach can be done in
*/
class AStarGraph
{
 public:

  /**
   * @brief gets the nodes adjacent to one
   * @param nodeId the id of node to which they are adjacent
   * @return the ids of the adjacent nodes
  */
  virtual const Vector<uint32>&
  getAdjacentNodes(uint32 nodeId);

  /**
   * @brief gets the distance between 2 nodes
   * @param nodeId1 the distance of the first node
   * @param nodeId2 the distance of the second node
   * @return the distance
  */
  virtual float
  getDistance(uint32 nodeId1, uint32 nodeId2);

  /**
   * @brief gets the cost of going from node1 to node2
   * @param nodeId1 the distance of the first node
   * @param nodeId2 the distance of the second node
   * @return the cost
  */
  virtual float
  getCost(uint32 nodeId1, uint32 nodeId2);

 private:

};

}



