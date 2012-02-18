
#ifndef SLG_NODE_H
#define SLG_NODE_H

#include <glm/glm.hpp>

namespace slg {
  
  struct Node
  {
    enum Type
    {
      Root = -1,
      None = -2,
      Error = -3
    };
  };
  
  typedef int NodeRef;
  
  class SceneGraph
  {
    public:
      SceneGraph(int maxNodeCount);
      ~SceneGraph();
      
      NodeRef createNode(NodeRef parent);
      NodeRef parentOf(NodeRef child);
      
      glm::vec3 position(NodeRef node);
      void setPosition(NodeRef node, glm::vec3 const& pos);
      
      int nodeCount() const { return m_nodeCount; }
      glm::mat4 * localTransform() const { return m_localTransform; }
      glm::mat4 * worldTransform() const { return m_worldTransform; }
      
    private:
      int m_nodeLimit;
      int m_nodeCount;
      
      NodeRef * m_parent;
      glm::mat4 * m_localTransform;
      glm::mat4 * m_worldTransform;
  };
  
  void updateWorldTransform(NodeRef const * parent, glm::mat4 const * localTransform, glm::mat4 * worldTransform, int nodeCount);
  
}

#endif