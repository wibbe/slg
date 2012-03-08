
uniform vec3 color;

varying vec3 normal;
varying vec2 texCoord;

uniform vec2 toolPos;
uniform float showTool;


void main()
{
  float NdotL = max(0.0, dot(normal, normalize(vec3(1, 0.8, 0.4))));

  float dist = distance(toolPos, texCoord);
  float amount = (dist < 0.03 ? 0.0 : (dist > 0.15 ? 0.0 : (1.0 - ((dist - 0.03) / 0.13)))) * showTool * 0.7;

  vec3 diffuseColor = vec3(0.2, 1, 0.4) * NdotL;
  vec3 toolColor = vec3(1.0, 0.2, 0.2) * NdotL;

  vec3 finalColor = diffuseColor * (1.0 - amount) + toolColor * amount;

  gl_FragColor = vec4(finalColor, 1.0);
}
