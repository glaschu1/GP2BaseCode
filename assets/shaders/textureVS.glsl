//#version 150
//
//out vec4 FragColor;
//
//void main(){
//	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//}

#version 150

in vec3 vertexPosition;
in vec2 vertexTexCoords;

out vec2 vertexTexCoordsOut;

uniform mat4 MVP;
void main(){
	vertexTexCoordsOut = vertexTexCoords;
	gl_Position = MVP*vec4(vertexPosition, 1.0);
}