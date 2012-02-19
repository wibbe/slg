/**
 * Copyright (c) 2012 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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