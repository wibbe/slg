
#include "slg/Buffer.hpp"

#include "GL/glew.h"

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
  
  Buffer::Buffer(Buffer const& copy)
    : m_id(copy.m_id),
      m_target(copy.m_target)
  {
  }
  
  Buffer::~Buffer()
  {
    glDeleteBuffers(1, &m_id);
  }
  
  Buffer const& Buffer::operator = (Buffer const& copy)
  {
    m_id = copy.m_id;
    m_target = copy.m_target;
    return *this;
  }
  
  void Buffer::bind() const
  {
    glBindBuffer(m_target, m_id);
  }
  
  void Buffer::unbind()
  {
    glBindBuffer(m_target, 0);
  }
  
  void Buffer::upload(void * data, int len, unsigned int mode)
  {
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
