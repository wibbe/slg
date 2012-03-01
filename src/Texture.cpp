
#include "slg/Texture.hpp"

#include "GL/glew.h"
#include "soil/SOIL.h"

namespace slg {
  
  Texture::Texture()
    : m_id(0),
      m_width(0),
      m_height(0)
  { }
  
  Texture::Texture(int width, int height, int format, unsigned char * data)
    : m_id(0),
      m_width(width),
      m_height(height)
  {
  	glGenTextures(1, &m_id);
  	glBindTexture(GL_TEXTURE_2D, m_id);

  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  
  Texture::Texture(Texture const& copy)
    : m_id(copy.m_id),
      m_width(copy.m_width),
      m_height(copy.m_height)
  { }
  
  Texture::~Texture()
  {
    glDeleteTextures(1, &m_id);
  }
  
  Texture const& Texture::operator = (Texture const& copy)
  {
    m_id = copy.m_id;
    m_width = copy.m_width;
    m_height = copy.m_height;
  }
  
  bool Texture::load(const char * filename)
  {
    m_id = SOIL_load_OGL_texture(filename,
                                 4, SOIL_CREATE_NEW_ID,
                                 SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT,
                                 &m_width,
                                 &m_height);
    return m_id != 0;
  }
  
  void Texture::bind(int unit)
  {
  
  }
  
  void Texture::unbind(int unit)
  {
  }
  
}
