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

#ifndef SLG_CAMERA_HPP
#define SLG_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace slg {
  
  class Camera
  {
    public:
      Camera();
      virtual ~Camera();
      
      void apply();
      
      void perspective(float fov, float aspect, float near, float far);
      
      void setPosition(glm::vec3 const& pos) { m_position = pos; }
      void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
      
      glm::vec3 const& position() const { return m_position; }
      
      glm::quat const& orientation() const { return m_orientation; }
      
      void move(float amount);
      void strafe(float amount);
      
      void yaw(float angle);
      void pitch(float angle);
      
    private:
      glm::vec3 m_position;
      glm::quat m_orientation;
      glm::mat4x4 m_projection;
  };
  
}

#endif