
#include "slg/Camera.hpp"

#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace slg {
  
  Camera::Camera()
    : m_position(),
      m_orientation(),
      m_projection()
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
  }
  
  void Camera::strafe(float amount)
  {
    m_position += glm::vec3(amount, 0.0f, 0.0f);
  }
  
  void Camera::yaw(float angle)
  {
    m_orientation = m_orientation * glm::rotate(glm::quat(), angle, glm::vec3(0, 1, 0));
  }
  
  void Camera::pitch(float angle)
  {
    m_orientation = glm::rotate(glm::quat(), angle, glm::vec3(1, 0, 0)) * m_orientation;
  }
  
  void Camera::apply()
  {
    glm::mat4x4 translate = glm::translate(-m_position);
    
    glm::mat4x4 result = translate * glm::toMat4(m_orientation);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(&m_projection[0][0]);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(&result[0][0]);
  }
  
}