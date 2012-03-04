
#include "slg/FrameBuffer.hpp"

#include "GL/glew.h"

#include <assert.h>
#include <stdio.h>

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

  FrameBuffer::~FrameBuffer()
  {
    glDeleteFramebuffers(1, &m_id);
  }

  void FrameBuffer::edit()
  {
    m_editing = true;
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
  }

  void FrameBuffer::done()
  {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      fprintf(stderr, "FrameBuffer error\n");
    }

    unbind();
    m_editing = false;
  }

  void FrameBuffer::addColorTexture(unsigned int internalFormat)
  {
    assert(m_editing && m_colorBufferCount < MAX_COLOR_BUFFERS);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorBufferCount, GL_TEXTURE_2D, texture, 0);

    m_colorBuffers[m_colorBufferCount++] = texture;
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
    }
  }

  void FrameBuffer::unbind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void FrameBuffer::bindTexture(int colorBuffer, int textureUnit)
  {
    assert(colorBuffer < m_colorBufferCount);
    
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_colorBuffers[colorBuffer]);
  }

  // -- FrameBufferTarget --

  FrameBufferTarget::FrameBufferTarget(FrameBuffer & buffer)
    : m_buffer(buffer)
  {
    glGetIntegerv(GL_VIEWPORT, m_viewport);
    m_buffer.bind();
    glViewport(0, 0, m_buffer.width(), m_buffer.height());
  }

  FrameBufferTarget::~FrameBufferTarget()
  {
    m_buffer.unbind();
    glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
  }
  
}

