
attribute vec3 inVertex;
attribute vec2 inTexCoord;

uniform mat4 modelViewProj;
uniform vec2 size;

varying vec2 texCoord;
varying float amount;

void main()
{
  gl_Position = modelViewProj * vec4(inVertex * vec3(size, 1), 1);
  texCoord = inTexCoord;
  
  amount = length(vec2(inTexCoord.x, 1.0 - inTexCoord.y)) / length(vec2(1.0, 1.0));
}