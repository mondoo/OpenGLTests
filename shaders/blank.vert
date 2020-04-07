#version 330

layout (location = 0) in vec3 pos;

out vec4 vColour;

uniform vec4 colour = vec4(1.0f);
uniform highp mat4 projection;
uniform highp mat4 view;
uniform highp mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vColour = colour;
}