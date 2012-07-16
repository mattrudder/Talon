#version 150

uniform mat4 matrixTransform;

in vec4 color;
in vec2 texCoord;
in vec4 position;

void main()
{
	gl_Position = position * matrixTransform;
}