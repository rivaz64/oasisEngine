#pragma once
#include "oaAStarGraph.h"
#include "oaIAForDec.h"
namespace oaEngineSDK{

class PlansGraph :
    public AStarGraph
{
 public:
 
  void
  buildGraph(const Vector<Action>& actions);

 private:
};

}



