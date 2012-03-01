
attribute vec3 inVertex;
attribute vec3 inNormal;

varying vec3 outNormal;

void main()
{
  gl_Position = gl_ModelViewProjectionMatrix * vec4(inVertex, 1.0);

  outNormal = gl_NormalMatrix * inNormal;
}
