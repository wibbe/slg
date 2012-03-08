
uniform vec3 color;

varying vec3 outNormal;
varying vec2 texCoord;

void main()
{
  gl_FragColor = vec4(texCoord.x, texCoord.y, 0, 1);
}
