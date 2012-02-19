
#include "slg/Texture.hpp"

#include "GL/glew.h"

#define STBI_HEADER_FILE_ONLY
#include "stb_image.c"

namespace slg {
  
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
  
  Texture::~Texture()
  {
    glDeleteTextures(1, &m_id);
  }
  
  Texture * Texture::loadFromFile(std::string const& filename)
  {
  	int width, height, components;

  	unsigned char * data = stbi_load(filename.c_str(), &width, &height, &components, 4);

  	if (data == NULL)
  		return 0;
  		
    Texture * texture = new Texture(width, height, GL_RGBA, data);
  	stbi_image_free(data);
  	
    return texture;
  }
  
}