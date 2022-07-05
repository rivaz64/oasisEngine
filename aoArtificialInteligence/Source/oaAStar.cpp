#include "oaAStar.h"
#include "oaAStarGraph.h"

namespace oaEngineSDK{

uint32 
AStar::getNextNodeForSearch(){
  uint32 id = *m_openList.begin();
  m_openList.pop_front();
  //m_closedList.push_back(id);
  return id;
}

void 
AStar::makePath()
{
  uint32 actualId = m_goalId;
  while(actualId != m_sourceId){
    m_path.push_back(actualId);
    actualId = m_paths[actualId];
  }
}

void
AStar::addNode(uint32 newId, uint32 parentId)
{
  m_nodes.emplace(pair<uint32,AStarNode>(newId,
  AStarNode(m_graph->getDistance(newId,m_goalId),m_graph->getCost(newId,m_sourceId))));
  addNodeToOpenList(newId);
}

void 
AStar::addNodeToOpenList(uint32 newId)
{
  auto fitness = m_nodes[newId].getFitness();
  for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
    if(fitness < m_nodes[*it].getFitness()){
      m_openList.insert(it,newId);
    }
  }
}

bool 
AStar::isBetterPath(uint32 nodeId, uint32 newParentId)
{
  float actualEuristic = m_nodes[nodeId].heuristic;
  float newEuristic = m_graph->getCost(nodeId,m_sourceId) + m_nodes[newParentId].heuristic;
  return newEuristic < actualEuristic;
}



SEARCH_STATE::E 
AStar::step()
{
  if(m_openList.empty()){
    return SEARCH_STATE::kFailed;
  }
  auto nodeId = getNextNodeForSearch();
  if(nodeId == m_goalId){
    makePath();
    return SEARCH_STATE::kPathFinded;
  }
  auto& adjacents = m_graph->getAdjacentNodes(nodeId);
  for(auto& adjacentId : adjacents){
    if(m_nodes.find(adjacentId) == m_nodes.end()){
      addNode(adjacentId,nodeId);
    }
    else if(isBetterPath(adjacentId,nodeId)){
      auto it = find(m_openList.begin(),m_openList.end(),adjacentId);
      if(it != m_openList.end()){
        m_openList.erase(it);
      }
      addNodeToOpenList(adjacentId);
    }
  }
  return SEARCH_STATE::kSearching;
}

}