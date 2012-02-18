
#ifndef SLG_TEXTURE_HPP
#define SLG_TEXTURE_HPP

#include <string>

namespace slg {
  
  class Texture
  {
    public:
      Texture(int width, int height, int format, unsigned char * data);
      ~Texture();
      
      int width() const { return m_width; }
      int height() const { return m_height; }
      
      static Texture * loadFromFile(std::string const& filename);
      
    private:
      unsigned int m_id;
      int m_width;
      int m_height;
  };
  
}

#endif