
#ifndef SLG_MESH_HPP
#define SLG_MESH_HPP

#include "slg/Buffer.hpp"
#include "slg/Shader.hpp"

namespace slg {
  
  class Mesh
  {
    public:
      enum Attributes
      {
        VERTEX,
        NORMAL,
        UV,
        TANGENT,
        BINORMAL,
        INDICIES,
        BUFFER_COUNT
      };
      
    private:
      Mesh(Mesh const& copy) { }
      Mesh const& operator = (Mesh const& copy) { return *this; }
      
    public:
      Mesh();
      ~Mesh();
      
      void destroy();
      bool load(const char * filename, bool useIndicies = true, bool computeTangents = false);

      template <typename T>
      void addBuffer(Attributes attrib, std::vector<T> const& data)
      {
        addBuffer(attrib, &data[0], data.size() * sizeof(T));
      }

      void addBuffer(Attributes attrib, const void * data, size_t size);
     
      void draw() const;
      
    private:
      Buffer * m_buffers[BUFFER_COUNT];
      
      unsigned int m_indexCount;
      bool m_loaded;
  };
  
}

#endif
