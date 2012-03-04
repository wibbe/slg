/**
 * Copyright (c) 2012 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SLG_FRAMEBUFFER_HPP
#define SLG_FRAMEBUFFER_HPP

namespace slg {
  
  class FrameBuffer
  {
    private:
      static const int MAX_COLOR_BUFFERS = 2;

      FrameBuffer(FrameBuffer const& copy) { } 
      FrameBuffer const& operator = (FrameBuffer const& copy) { return *this; }

    public:
      FrameBuffer(int width, int height);
      ~FrameBuffer();


      void edit();
      void done();

      /**
       * Create and attach a texture to the framebuffer
       * 
       * Format can be one of the following:
       * - GL_RGB, GL_RGBA, GL_ALPHA, and so on...
       * 
       * Type should be:
       * - GL_UNSIGNED_BYTE, GL_FLOAT, GL_R32F
       */
      void addColorTexture(unsigned int internalFormat);
      void addDepthTexture();
      void addDepthBuffer();

      int width() const { return m_width; }
      int height() const { return m_height; }

      void bind();
      void unbind();

    private:
      unsigned int m_id;
      int m_width;
      int m_height;

      unsigned int m_depthBuffer;
      unsigned int m_colorBuffers[MAX_COLOR_BUFFERS];
      int m_colorBufferCount;

      bool m_editing;
  };


  /**
   * Helper class that binds a FrameBuffer and sets up a
   * correct viewport for it.
   */
  class FrameBufferState
  {
    public:
      FrameBufferState(FrameBuffer & buffer);
      ~FrameBufferState();

    private:
      FrameBuffer & m_buffer;
      int m_viewport[4];
  };
  
}

#endif
