
attribute vec3 inVertex;
attribute vec2 inTexCoord;

varying vec2 texCoord;

void main()
{
  gl_Position = vec4(inVertex, 1);
  texCoord = inTexCoord;
}
