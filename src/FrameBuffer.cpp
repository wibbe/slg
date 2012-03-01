
#include "slg/FrameBuffer.hpp"

#include "GL/glew.h"

#include <assert.h>

namespace slg {
  
  FrameBuffer::FrameBuffer(int width, int height)
    : m_id(0),
      m_width(width),
      m_height(height),
      m_editing(false),
      m_depthBuffer(0),
      m_colorBufferCount(0)
  {
    glGenFramebuffers(1, &m_id);

    for (int i = 0; i < MAX_COLOR_BUFFERS; ++i)
      m_colorBuffers[i] = 0;
  }

  FrameBuffer::FrameBuffer(FrameBuffer const& copy)
    : m_id(copy.m_id),
      m_width(copy.m_width),
      m_height(copy.m_height),
      m_editing(copy.m_editing),
      m_depthBuffer(copy.m_depthBuffer),
      m_colorBufferCount(copy.m_colorBufferCount)
  {
    for (int i = 0; i < MAX_COLOR_BUFFERS; ++i)
      m_colorBuffers[i] = copy.m_colorBuffers[i];
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
    m_editing = copy.m_editing;
    m_depthBuffer = copy.m_depthBuffer;
    m_colorBufferCount = copy.m_colorBufferCount;

    for (int i = 0; i < MAX_COLOR_BUFFERS; ++i)
      m_colorBuffers[i] = copy.m_colorBuffers[i];

    return *this;
  }

  void FrameBuffer::edit()
  {
    m_editing = true;
    bind();
  }

  void FrameBuffer::done()
  {
    unbind();
    m_editing = false;
  }

  void FrameBuffer::addColorTexture(unsigned int format, unsigned int type)
  {
    assert(m_editing && m_colorBufferCount < MAX_COLOR_BUFFERS);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, type, 0);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorBufferCount, texture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_colorBuffers[m_colorBufferCount++] = texture;
  }

  void FrameBuffer::addDepthTexture()
  {
    assert(m_editing);
  }

  void FrameBuffer::addDepthBuffer()
  {
    assert(m_editing && m_depthBuffer == 0);
    
    glGenRenderbuffers(1, &m_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
  }

  void FrameBuffer::bind()
  {
    if (!m_editing)
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

