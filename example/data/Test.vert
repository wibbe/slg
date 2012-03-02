
attribute vec3 inVertex;
attribute vec3 inNormal;

uniform mat4 modelViewProj;
uniform mat4 model;

varying vec3 outNormal;

void main()
{
  gl_Position = modelViewProj * vec4(inVertex, 1.0);

  outNormal = (model * vec4(inNormal, 0.0)).xyz;
}
