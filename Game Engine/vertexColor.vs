#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 transform;
uniform mat4 projection;


out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position =projection*transform* vec4(aPos, 1.0);
	ourColor = vec3(1,0,0);
	
}