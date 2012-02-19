
#include "slg/Camera.hpp"

#include "GL/glew.h"

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
    m_projection.identity();
    m_projection.perspective(fov, aspect, near, far);
  }
  
  void Camera::move(float amount)
  {
    m_position += Vector3(0.0f, 0.0f, -amount);
  }
  
  void Camera::strafe(float amount)
  {
    m_position += Vector3(amount, 0.0f, 0.0f);
  }
  
  void Camera::yaw(float angle)
  {
    m_orientation = m_orientation * Quaternion(Vector3(0, 1, 0), degToRad(angle));
  }
  
  void Camera::pitch(float angle)
  {
    m_orientation = Quaternion(Vector3(1, 0, 0), degToRad(angle)) * m_orientation;
  }
  
  void Camera::apply()
  {
    Matrix4 translate;
    translate.translate(-m_position);
    
    Matrix4 result = translate * m_orientation.toMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_projection.load();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    result.load();
  }
  
}