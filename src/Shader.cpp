
#include "GL/glew.h"

#include "slg/Shader.hpp"
#include "slg/File.hpp"

#include <cassert>

namespace slg {

  static void showLogInfo(GLuint object, 
  								        void (*glGet__iv)(GLuint, GLenum, GLint*),
  								        void (*glGet__InfoLog)(GLuint, GLsizei, GLsizei*, GLchar*))
  {
  	int logLength;
  	char * log;
  	
  	glGet__iv(object, GL_INFO_LOG_LENGTH, &logLength);
  	log = new char[logLength];
  	glGet__InfoLog(object, logLength, NULL, log);
  	fprintf(stderr, "%s", log);

  	delete[] log;
  }

  Shader::Shader()
    : m_program(0),
      m_shaderCount(0)
  {
    for (int i = 0; i < MAX_SHADERS; ++i)
      m_shaders[i] = 0;
  }
  
  Shader::~Shader()
  {
    destroy();
  }

  void Shader::destroy()
  {
    for (int i = 0; i < MAX_SHADERS; ++i)
    {
      if (m_shaders[i])
        glDeleteShader(m_shaders[i]);
      m_shaders[i] = 0;
    }

    if (m_program)
	  	glDeleteProgram(m_program);

	  m_program = 0;
  }

  bool Shader::load(const char * filename, unsigned int type)
  {
    assert(m_shaderCount < MAX_SHADERS);
    
    int length;
    char * data = 0;
    
    if (!fileContent(filename, &data, length))
      return false;

    GLuint shader = glCreateShader(type);
	  glShaderSource(shader, 1, (const GLchar **)&data, &length);
	  glCompileShader(shader);

	  delete[] data;
	  
	  int ok;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	  if (!ok)
	  {
	  	fprintf(stderr, "Failed to compile shader: %s\n", filename);
	  	showLogInfo(shader, glGetShaderiv, glGetShaderInfoLog);
	  	destroy();
	  	return false;
	  }

	  m_shaders[m_shaderCount++] = shader;

    return true;
  }

  bool Shader::link()
  {
    m_program = glCreateProgram();

    for (int i = 0; i <m_shaderCount; ++i)
      glAttachShader(m_program, m_shaders[i]);

    glLinkProgram(m_program);

    int ok;
	  glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
	  if (!ok)
	  {
	  	fprintf(stderr, "Failed to link shader program:\n");
	  	showLogInfo(m_program, glGetProgramiv, glGetProgramInfoLog);
	  	destroy();
	  	return false;
	  }

	  return true;
  }
void Shader::bind()
  {
  }

  void Shader::unbind()
  {
  }
  
}
