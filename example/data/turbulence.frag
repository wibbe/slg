
uniform sampler2D previous;
uniform float dt;
uniform vec2 pos;

varying vec2 texCoord;

void main()
{
  float current = texture2D(previous, texCoord).r;
  float h = turbulence(texCoord * 5.0, 4.0, 2.0, 0.5);

  float dist = distance(pos, texCoord);

  float amount = dist < 0.03 ? 1.0 : (dist > 0.15 ? 0.0 : (1.0 - ((dist - 0.03) / 0.13)));

  float finalHeight = current + h * dt * amount;
  gl_FragColor = vec4(vec3(finalHeight), 1);
}

