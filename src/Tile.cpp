
#include "slg/Tile.hpp"
#include "slg/MeshHelpers.hpp"

#include "glm/gtx/transform.hpp"

namespace slg {
  
  Tile::Tile()
    : m_quad(),
      m_margin(5),
      m_mousePos(0, 0),
      m_mouseDown(false),
      m_hit(false),
      m_mouseState(NONE)
  {
    createQuad(m_quad, false);
    
    m_textureShader.load("../../example/data/tile.vert", GL_VERTEX_SHADER);
    m_textureShader.load("../../example/data/tileTexture.frag", GL_FRAGMENT_SHADER);
    m_textureShader.setupMeshAttributes();
    m_textureShader.link();
  }
  
  void Tile::begin(glm::mat4 const& projection, glm::ivec2 const& mousePos, bool mouseDown)
  {
    m_projection = projection;
    m_mousePos = mousePos;
    m_hit = false;
    
    if (!m_mouseDown && mouseDown)
      m_mouseState = PRESS;
    else if (m_mouseDown && !mouseDown)
      m_mouseState = RELEASE;
    else
      m_mouseState = NONE;
    
    m_mouseDown = mouseDown;
  }
  
  void Tile::pushRow()
  {
    State state;
    state.dir = ROW;
    state.max = 0;
    state.pos = position();
    
    m_state.push(state);
  }
  
  void Tile::pushStack()
  {
    State state;
    state.dir = STACK;
    state.max = 0;
    state.pos = position();
    
    m_state.push(state);
  }
  
  void Tile::pop()
  {
    m_state.pop();
  }
  
  bool Tile::icon(Texture & tex, int padding)
  {
    glm::ivec2 pos = position();
    
    float width = tex.width() + padding * 2;
    float height = tex.height() + padding * 2;
    
    tex.bind(0);
    
    m_textureShader.bind();
    m_textureShader.uniform("texture", 0);
    m_textureShader.uniform("size", width, height);
    m_textureShader.uniform("modelViewProj", m_projection * glm::translate((float)pos.x, (float)pos.y, 0.0f));
    m_quad.draw();
    m_textureShader.unbind();
    
    tex.unbind(0);
    
    advance(width, height);
    
    bool inside = isInside(pos, glm::ivec2(width, height), m_mousePos);
    m_hit |= inside && (m_mouseState == RELEASE || m_mouseDown);
    
    return inside && (m_mouseState == RELEASE);
  }
  
  void Tile::advance(int width, int height)
  {
    assert(!m_state.empty());
    
    if (state().dir == ROW)
    {
      state().max = glm::max(height, state().max);
      state().pos.x += width + m_margin;
    }
    else
    {
      state().max = glm::max(width, state().max);
      state().pos.y += height + m_margin;
    }
  }
  
  bool Tile::isInside(glm::ivec2 const& start, glm::ivec2 const& size, glm::ivec2 const& point)
  {
    return point.x >= start.x &&
           point.y >= start.y &&
           point.x <= (start.x + size.x) &&
           point.y <= (start.y + size.y);
  }
  
  glm::ivec2 Tile::position()
  {
    if (m_state.empty())
      return glm::ivec2(m_margin, m_margin);
      
    return state().pos;
  }
  
}