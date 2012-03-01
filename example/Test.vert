
attribute vec3 vertex;
attribute vec3 normal;

varying vec3 norm;

void main()
{
  gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex, 1.0);

  norm = normal;
}
