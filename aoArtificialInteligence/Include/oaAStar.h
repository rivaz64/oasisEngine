#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaIAForDec.h"
#include "oaAStarNode.h"

namespace oaEngineSDK{

namespace SEARCH_STATE{
enum E{
kFailed = 0,
kSearching,
kPathFinded 
};
}

/**
 * @brief class for doing aStar searches
*/
class AStar
{
 public:

  /**
   * @brief executes a step of the search.
   * @return the state of the search at the end of the state
  */
  SEARCH_STATE::E 
  step();

  /**
   * @brief 
   * @param  
  */
  FORCEINLINE void
  run()
  {
    reset();
    while(step() != SEARCH_STATE::kSearching);
  }

  /**
   * @brief sets the node for the start of the search
  */
  FORCEINLINE void
  setSourceId(uint32 sourceId)
  {
    m_sourceId = sourceId;
  }

  /**
   * @brief sets the node that is the goal of the search
  */
  FORCEINLINE void
  setGoalId(uint32 goalId)
  {
    m_goalId = goalId;
  }

  /**
   * @brief clears the data and prepares it for a new search
  */
  FORCEINLINE void
  reset()
  {
    m_openList.clear();
    m_nodes.clear();
    m_paths.clear();
    m_path.clear();
    addNode(m_sourceId,-1);
    m_openList.push_back(m_sourceId);
  }

  FORCEINLINE Vector<uint32>
  getPath()
  {
    return m_path;
  }

  FORCEINLINE void
  setGraph(SPtr<AStarGraph> graph)
  {
    m_graph = graph;
  }

 private:

  /**
   * @brief gets the id of the node for doing the search
   * @return 
  */
  uint32 
  getNextNodeForSearch();

  /**
   * @brief after geting to the end it finds the path backwards
   * @param id 
  */
  void
  makePath();

  /**
   * @brief adds a node to the search
   * @param nodeId tthe node to be added
  */
  void 
  addNode(uint32 newId, uint32 parentId);

  /**
   * @brief adds the node to the open list
   * @param newId the id of the node to add
  */
  void
  addNodeToOpenList(uint32 newId);

  bool
  isBetterPath(uint32 nodeId, uint32 newParentId);

  /**
   * @brief all the search Nodes
  */
  map<uint32,AStarNode> m_nodes;

  /**
   * @brief the paths that have been searched
  */
  //Vector<uint32> m_closedList;

  /**
   * @brief the paths in wait for search
  */
  List<uint32> m_openList;

  /**
   * @brief the graph with all the paths
   * keys are the nodes and values are the parents
  */
  Map<uint32,uint32> m_paths;

  /**
   * @brief the path of id nodes
  */
  Vector<uint32> m_path;

  /**
   * @brief from where to start the search
  */
  uint32 m_sourceId;

  /**
   * @brief where the search has to end
  */
  uint32 m_goalId;

  /**
   * @brief the graph to do the search in
  */
  SPtr<AStarGraph> m_graph;
};

}


