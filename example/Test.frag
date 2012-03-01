
uniform vec3 color;

varying vec3 norm;

void main()
{
  float NdotL = clamp(dot(norm, vec3(0, 1, 0)), 0.0, 1.0);

  gl_FragColor = vec4(color * NdotL, 1);
}
