#version 150


out vec4 FragColor;

in vec2 textureCoords;
uniform float time;
uniform vec2 resolution;
uniform	sampler2D texture0;

void main()
{
  vec2 newTextureCoords=textureCoords;
  newTextureCoords.x += sin(time)*0.1;
  newTextureCoords.y += cos(time)*0.1;
  FragColor = texture(texture0, newTextureCoords);
 
  
  //gl_FragColur = vec4(col,1.0);
  //FragColor = texture(texture0,	textureCoords).bbba;
}

