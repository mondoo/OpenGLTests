#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec4 vColour;
out vec2 texCoord;

uniform vec4 colour = vec4(1.0f);
uniform highp mat4 projection;
uniform highp mat4 view;
uniform highp mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vColour = colour;
	texCoord = tex;
}