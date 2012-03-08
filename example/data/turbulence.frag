
uniform sampler2D previous;
uniform float dt;

varying vec2 texCoord;

float turbulence(vec2 p, float octaves, float lacunarity, float gain)
{
    float sum = 0.0;
    float freq = 1.0, amp = 1.0;
    for (float i = 0.0; i < octaves; i++)
    {
        float n = snoise(p * freq);
        sum += n * amp;
        freq *= lacunarity;
        amp *= gain;
    }
    return sum;
}

void main()
{
  float current = texture2D(previous, texCoord).r;
  float h = turbulence(texCoord * 5.0, 4.0, 2.0, 0.5);
  gl_FragColor = vec4(vec3(current + h * dt), 1);

  //gl_FragColor = vec4(vec3(texCoord.x * texCoord.y), 1);

}

