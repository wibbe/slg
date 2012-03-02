
#include "slg/Camera.hpp"

#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace slg {
  
  Camera::Camera()
    : m_changed(true),
      m_position(),
      m_orientation(),
      m_projection(),
      m_view()
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
    m_position += glm::vec3(0.0f, 0.0f, -amount);
    m_changed = true;
  }
  
  void Camera::strafe(float amount)
  {
    m_position += glm::vec3(amount, 0.0f, 0.0f);
    m_changed = true;
  }
  
  void Camera::yaw(float angle)
  {
    m_orientation = m_orientation * glm::rotate(glm::quat(), angle, glm::vec3(0, 1, 0));
    m_changed = true;
  }
  
  void Camera::pitch(float angle)
  {
    m_orientation = glm::rotate(glm::quat(), angle, glm::vec3(1, 0, 0)) * m_orientation;
    m_changed = true;
  }
  
  void Camera::update()
  {
    if (m_changed)
    {
      glm::mat4 translate = glm::translate(-m_position);
      m_view = glm::toMat4(m_orientation) * translate;
      m_changed = true;
    }    
  }
 
}
