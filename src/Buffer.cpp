
#include "slg/Buffer.hpp"

#include "GL/glew.h"
#include <assert.h>

namespace slg {
  
  Buffer::Buffer()
    : m_id(0),
      m_target(0)
  { }
  
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
  
  void Buffer::bind() const
  {
    glBindBuffer(m_target, m_id);
  }
  
  void Buffer::upload(const void * data, int len, unsigned int mode)
  {
    assert(m_id != 0);
    
    glBindBuffer(m_target, m_id);
    glBufferData(m_target, len, data, mode);
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
