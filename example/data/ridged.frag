
uniform sampler2D previous;
uniform float dt;
uniform vec2 pos;

varying vec2 texCoord;

void main()
{
  float current = texture2D(previous, texCoord).r;
  float h = ridgedTurbulence(texCoord * 5.0, 4.0, 2.0, 0.5);

  float dist = distance(pos, texCoord);

  float finalHeight = current + (dist < 0.1 ? (h * dt) : 0.0);
  gl_FragColor = vec4(vec3(finalHeight), 1);
}

