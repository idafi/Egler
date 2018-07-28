#version 330

uniform mat4 localToCameraMatrix;
uniform mat4 perspectiveMatrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 _color;

out vec4 color;

void main()
{
	vec4 cameraPos = localToCameraMatrix * position;
	gl_Position = perspectiveMatrix * cameraPos;
	
	color = _color;
}