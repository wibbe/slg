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

#ifndef SLG_MATRIX4_HPP
#define SLG_MATRIX4_HPP

#include "slg/Vector3.hpp"

namespace slg {
  
  class Matrix4
  {
    public:
      Matrix4();
      Matrix4(Matrix4 const& mat);
      Matrix4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33);
      
      void identity();
      
      void translate(Vector3 const& pos);
      void scale(Vector3 const& scale);
      void perspective(float fov, float aspect, float near, float far);
      
      /// Upload matrix to OpenGL.
      void load();
      
      Matrix4 operator * (Matrix4 const& mat) const;
      
      inline float operator [] (int index) const { return m[index]; }
      
      float const * data() const { return &m[0]; }
      
    private:
      float m[16];
  };
  
}

#endif