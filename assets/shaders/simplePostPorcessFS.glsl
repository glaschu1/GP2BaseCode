#version 150


//out vec4 FragColor;

in vec2 textureCoords;
uniform float time;
uniform vec2 resolution;
uniform	sampler2D texture0;

void main(void)
{
  vec2 cPos = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
  float cLength = length(cPos);
  
  vec2 uv = gl_FragCoord.xy/resolution.xy+(cPos/cLength)*cos(cLength*12.0-time*4.0)*0.03;
  vec3 col = texture2D(texture0,uv).xyz;
  
  gl_FragColor = vec4(col,1.0);
  //FragColor = texture(texture0,	textureCoords).bbba;
}

