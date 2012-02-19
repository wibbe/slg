
#ifndef SLG_BUFFER_COLLECTION_HPP
#define SLG_BUFFER_COLLECTION_HPP

#include "slg/Buffer.hpp"

namespace slg {
  
  class BufferCollection
  {
    public:
      enum Mapping
      {
        VERTEX,
        NORMAL,
        TEX0,
        TEX1,
        TEX2,
        TEX3,
        TEX4,
        INDICES
      };
      
      enum Primitive
      {
        TRIANGLES,
        QUADS
      };
      
    public:
      BufferCollection();
      ~BufferCollection();
      
      void setPrimitiveType(Primitive type) { m_type = type; }
      void setPrimitiveCount(unsigned int count) { m_count = count; }
      
      void append(Buffer const& buffer, int elementCount, Mapping mapping);
      
      void draw();
      
    private:
      struct Stream
      {
        Buffer buffer;
        Mapping mapping;
        int elementCount;
      };
      
      std::vector<Stream> m_streams;
      Primitive m_type;
      unsigned int m_count;
  };
  
}

#endif