#version 150

in vec2 textureCoords;
uniform float time;
uniform vec2 resolution;
uniform sampler2D texture0;
out vec4 FragColor;

void main() {
    vec2 newTextureCoords=textureCoords;
  vec2 cPos = -1.0 + 2.0 * gl_FragCoord.xy / newTextureCoords.xy;
  float cLength = length(cPos);
  
  vec2 uv = gl_FragCoord.xy/newTextureCoords.xy+(cPos/cLength)*cos(cLength*12.0-time*4.0)*0.03;
  vec3 col = texture(texture0,uv).xyz;
  
  FragColor = vec4(col,1.0);
}
