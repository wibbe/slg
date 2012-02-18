
#include "slg/Node.hpp"
#include <cassert>

namespace slg {
  
  // -- SceneGraph
  
  SceneGraph::SceneGraph(int maxNodeCount)
    : m_nodeLimit(maxNodeCount),
      m_nodeCount(-1),
      m_parent(new NodeRef[m_nodeLimit]),
      m_localTransform(new glm::mat4[m_nodeLimit]),
      m_worldTransform(new glm::mat4[m_nodeLimit])
  {
  }
  
  SceneGraph::~SceneGraph()
  {
    delete[] m_parent;
    delete[] m_localTransform;
    delete[] m_worldTransform;
  }
  
  NodeRef SceneGraph::createNode(NodeRef parent)
  {
    if ((m_nodeCount + 1) >= m_nodeLimit)
      return Node::Error;
    
    NodeRef node = ++m_nodeCount;
    m_parent[node] = parent;
    
    return node;
  }
  
  NodeRef SceneGraph::parentOf(NodeRef child)
  {
    if (child >= 0 && child <= m_nodeCount)
      return m_parent[child];
      
    return Node::Error;
  }
  
  glm::vec3 SceneGraph::position(NodeRef node)
  {
    assert(node >= 0 && node <= m_nodeCount);
    return glm::vec3(m_localTransform[node][3]);
  }
  
  void SceneGraph::setPosition(NodeRef node, glm::vec3 const& pos)
  {
    assert(node >= 0 && node <= m_nodeCount);
    m_localTransform[node][3] = glm::vec4(pos, 1.0f);
  }
  
  // -- Algorithms 
  
  void updateWorldTransform(NodeRef const * parent, glm::mat4 const * localTransform, glm::mat4 * worldTransform, int nodeCount)
  {
    for (int i = 0; i < nodeCount; ++i)
    {
      if (parent[i] == Node::Root)
        worldTransform[i] = localTransform[i];
      else
        worldTransform[i] = worldTransform[parent[i]] * localTransform[i];
    }
  }
  
}