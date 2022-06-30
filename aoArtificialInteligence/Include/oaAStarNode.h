#pragma once
#include "oaPrerequisitesUtilities.h"
namespace oaEngineSDK{

/**
 * @brief node used for building the graph used for AStar search;
*/
struct AStarNode
{
 public:
 
  AStarNode(float _toGoal, float _heuristic) :
   toGoal(_toGoal), heuristic(_heuristic) {}

  FORCEINLINE float
  getFitness(){
    return toGoal+heuristic;
  }

  /**
   * @brief the distance from this node to the goal
  */
  float toGoal;

  /**
   * @brief the cost from the source to this node
  */
  float heuristic;
};

}


