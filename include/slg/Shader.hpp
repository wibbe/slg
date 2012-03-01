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

#ifndef SLG_SHADER_HPP
#define SLG_SHADER_HPP

namespace slg {
  
  class Shader
  {
    private:
      static const int MAX_SHADERS = 4;

    public:
      Shader();
      Shader(Shader const& copy);
      ~Shader();

      void destroy();

      Shader const& operator = (Shader const& copy);

      /// Load a new shader of the supplied type.
      /// Type can be one of the following:
      /// * GL_VERTEX_SHADER
      /// * GL_FRAGMENT_SHADER
      bool load(const char * filename, unsigned int type);

      bool link();

      void bind();
      void unbind();

      void uniform(const char * name, float x);
      void uniform(const char * name, float x, float y);
      void uniform(const char * name, float x, float y, float z);
      void uniform(const char * name, float x, float y, float z, float w);
      
      void attribute(unsigned int index, const char * name) const;

    private:
      unsigned int m_program;
      unsigned int m_shaders[MAX_SHADERS];
      unsigned short m_shaderCount;
  };
  
}

#endif
