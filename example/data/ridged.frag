
uniform sampler2D previous;
uniform float dt;

varying vec2 texCoord;

void main()
{
  float current = texture2D(previous, texCoord).r;
  float h = ridgedTurbulence(texCoord * 5.0, 4.0, 2.0, 0.5);
  gl_FragColor = vec4(vec3(current + h * dt), 1);
}

