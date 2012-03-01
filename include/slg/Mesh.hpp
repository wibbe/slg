
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
        UV,
        NORMAL,
        TANGENT,
        BINORMAL
      };
    
    public:
      Mesh();
      Mesh(Mesh const& copy);
      ~Mesh();
      
      void destroy();
      
      Mesh const& operator = (Mesh const& copy);
      
      bool load(const char * filename, bool useIndicies = true, bool computeTangents = false);
      
      void draw(Shader const& shader) const;
      
    private:
      Buffer m_vertex;
      Buffer m_uv;
      Buffer m_normal;
      Buffer m_tangent;
      Buffer m_binormal;
      Buffer m_indicies;
      
      unsigned int m_indexCount;
      
      bool m_hasTangents;
      bool m_useIndicies;
      bool m_loaded;
  };
  
}

#endif