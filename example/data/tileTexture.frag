
uniform sampler2D texture;

varying vec2 texCoord;
varying float amount;

void main()
{
  vec4 texColor = texture2D(texture, texCoord);
  
  vec3 color = mix(vec3(1.0, 192.0 / 255.0, 132.0 / 255.0), vec3(1.0, 0.5, 0.0), amount);

  gl_FragColor = vec4(color * (1.0 - texColor.a) + texColor.rgb * texColor.a, 1);
}