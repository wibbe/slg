
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
      m_orientation(),
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
    m_position += glm::inverse(m_orientation) * glm::vec3(0.0f, 0.0f, -amount);
    m_changed = true;
  }
  
  void Camera::strafe(float amount)
  {
    m_position += glm::inverse(m_orientation) * glm::vec3(amount, 0.0f, 0.0f);
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

  void Camera::roll(float angle)
  {
    m_euler.z += glm::radians(angle);
    m_changed = true;
  }
  
  void Camera::update()
  {
    if (m_changed)
    {
      m_view = glm::toMat4(m_orientation) * glm::translate(-m_position);
      m_changed = false;
    }    
  }

  glm::vec3 Camera::pick(glm::ivec2 const& mousePos)
  {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLfloat zCursor;
    float winX = (float)mousePos.x;
    float winY = (float)viewport[3] - (float)mousePos.y;
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);

    glm::vec3 pos = glm::unProject(glm::vec3(winX, winY, zCursor), m_view, m_projection, 
                                   glm::ivec4(viewport[0], viewport[1], viewport[2], viewport[3]));

    //printf("World pos: %s\n", glm::to_string(pos).c_str());
    return pos;
  }

  /*
 GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];
GLfloat winX,winY;
glGetIntegerv(GL_VIEWPORT, viewport);
glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
glGetDoublev(GL_PROJECTION_MATRIX, projection);

// obtain the Z position (not world coordinates but in range 0 - 1)
GLfloat z_cursor;
winX = (float)x_cursor;
winY = (float)viewport[3]-(float)y_cursor;
glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

// obtain the world coordinates
GLdouble x, y, z;
gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &x, &y, &z);
*/
}
