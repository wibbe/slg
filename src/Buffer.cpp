
#include "slg/Buffer.hpp"

#include "GL/glew.h"

namespace slg {
  
  Buffer::Buffer(int target)
    : m_id(0),
      m_target(target)
  {
    glGenBuffers(1, &m_id);
  }
  
  Buffer::~Buffer()
  {
    glDeleteBuffers(1, &m_id);
  }
  
  void Buffer::bind()
  {
    glBindBuffer(m_target, m_id);
  }
  
  void Buffer::unbind()
  {
    glBindBuffer(m_target, 0);
  }
  
  void Buffer::upload(void * data, int len, Mode mode)
  {
    glBufferData(m_target, len, data, mode == STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
  }
  
  // -- VertexBuffer --
  
  VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER)
  {
  }
  
  // -- IndexBuffer --
  
  IndexBuffer::IndexBuffer()
    : Buffer(GL_ELEMENT_ARRAY_BUFFER)
  {
  }
}