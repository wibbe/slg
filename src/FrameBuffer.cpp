
#include "slg/FrameBuffer.hpp"

#include "GL/glew.h"

namespace slg {
  
  FrameBuffer::FrameBuffer(int width, int height)
    : m_id(0),
      m_width(width),
      m_height(height)
  {
    glGenFramebuffers(1, &m_id);
  }

  FrameBuffer::FrameBuffer(FrameBuffer const& copy)
    : m_id(copy.m_id),
      m_width(copy.m_width),
      m_height(copy.m_height)
  {
  }
  
  FrameBuffer::~FrameBuffer()
  {
    glDeleteFramebuffers(1, &m_id);
  }

  FrameBuffer const& FrameBuffer::operator = (FrameBuffer const& copy)
  {
    m_id = copy.m_id;
    m_width = copy.m_width;
    m_height = copy.m_height;

    return *this;
  }

  void FrameBuffer::addColorTexture(unsigned int format, unsigned int type)
  {
    bind();

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, type, 0);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    unbind();
  }

  void FrameBuffer::addDepthTexture()
  {
  }

  void FrameBuffer::addDepthBuffer()
  {
  }

  void FrameBuffer::bind()
  {
    if (m_id)
    {
      glBindFramebuffer(GL_FRAMEBUFFER, m_id);
      glViewport(0, 0, m_width, m_height);
    }
  }

  void FrameBuffer::unbind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
}

