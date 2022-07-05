#pragma once
#include "oaAStarGraph.h"
#include "oaIAForDec.h"
namespace oaEngineSDK{

class oaPlansGraph :
    public AStarGraph
{
 public:
 
  void
  buildGraph(const Vector<Action>& actions);

 private:
};

}



