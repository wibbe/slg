
uniform vec3 color;

varying vec3 outNormal;

void main()
{
  gl_FragColor = vec4(color, 1);
}
