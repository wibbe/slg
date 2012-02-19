
#include "slg/BufferCollection.hpp"

#include "GL/glew.h"

namespace slg {
  
  BufferCollection::BufferCollection()
    : m_type(TRIANGLES),
      m_count(0)
  { 
  }
  
  BufferCollection::~BufferCollection()
  {
  }
  
  void BufferCollection::append(Buffer const& buffer, int elementCount, Mapping mapping)
  {
    Stream stream;
    stream.buffer = buffer;
    stream.mapping = mapping;
    stream.elementCount = elementCount;
    
    m_streams.push_back(stream);
  }
  
  void BufferCollection::draw()
  {
    for (std::vector<Stream>::const_iterator it = m_streams.begin(), end = m_streams.end(); it != end; ++it)
    {
      Stream const& stream = *it;
      
      stream.buffer.bind();
      
      switch (stream.mapping)
      {
        case VERTEX:
          glVertexPointer(stream.elementCount, GL_FLOAT, 0, 0);
          break;
        
        case NORMAL:
          glNormalPointer(GL_FLOAT, 0, 0);
          break;
        
        case TEX0:
        case TEX1:
        case TEX2:
        case TEX3:
          break;
        
        case INDICES:
          break;
      }
    }
  }
  
}