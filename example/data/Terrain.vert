
attribute vec3 inVertex;

varying vec2 texCoord;
varying vec3 normal;

uniform mat4 modelViewProj;
uniform mat4 model;
uniform vec2 texOffset;
uniform vec2 texScale;
uniform vec2 texelSize;

uniform sampler2D heightMap;

void main()
{
  vec2 uv = texOffset + inVertex.xz * texScale;
  texCoord = uv;

  float height = texture2D(heightMap, uv).x;

  float heightU = texture2D(heightMap, uv + vec2(texelSize.x, 0.0)).x;
  float heightV = texture2D(heightMap, uv + vec2(0.0, texelSize.y)).x;

  vec3 u = normalize(vec3(0.5, heightU - height, 0.0));
  vec3 v = normalize(vec3(0, heightU - height, 0.5));
  normal = cross(v, u);

  gl_Position = modelViewProj * vec4(inVertex + vec3(0, height, 0), 1.0);
}

