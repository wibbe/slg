
attribute vec3 inVertex;

uniform mat4 modelViewProj;
uniform mat4 model;
uniform vec2 texOffset;
uniform vec2 texScale;

uniform sampler2D heightMap;

void main()
{
  vec2 uv = texOffset + inVertex.xz * texScale;

  float height = texture2D(heightMap, uv).x;

  gl_Position = modelViewProj * vec4(inVertex + vec3(0, height, 0), 1.0);
}

