
#include "slg/Camera.hpp"

#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

namespace slg {
  
  Camera::Camera()
    : m_changed(true),
      m_euler(),
      m_position(),
      m_orientation(1.0),
      m_projection(1.0),
      m_view(1.0)
  {
  }
  
  Camera::~Camera()
  {
  }
  
  void Camera::perspective(float fov, float aspect, float near, float far)
  {
    m_projection = glm::perspective(fov, aspect, near, far);
  }
  
  void Camera::move(float amount)
  {
    m_position += glm::vec3(glm::transpose(m_orientation) * glm::vec4(0.0f, 0.0f, -amount, 0.0f));
    m_changed = true;
  }
  
  void Camera::strafe(float amount)
  {
    m_position += glm::vec3(glm::transpose(m_orientation) * glm::vec4(amount, 0.0f, 0.0f, 0.0f));
    m_changed = true;
  }
  
  void Camera::yaw(float angle)
  {
    m_euler.y += glm::radians(angle);
    m_changed = true;
  }
  
  void Camera::pitch(float angle)
  {
    m_euler.x += glm::radians(angle);
    m_changed = true;
  }

  void Camera::roll(float angle)
  {
    m_euler.z += glm::radians(angle);
    m_changed = true;
  }
  
  void Camera::update()
  {
    if (m_changed)
    {
      m_orientation = glm::yawPitchRoll(m_euler.y, m_euler.x, m_euler.z);
      m_view = m_orientation * glm::translate(-m_position);

      m_changed = false;
    }    
  }
 
}
