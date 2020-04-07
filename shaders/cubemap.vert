#version 330

layout (location = 0) in vec3 pos;

out vec4 vColour;
out vec3 texCoord;

uniform vec4 colour = vec4(1.0f);
uniform highp mat4 projection;
uniform highp mat4 view;

void main()
{
	vColour = colour;
	texCoord = pos;
	vec4 position = projection * view * vec4(pos, 1.0f);
	gl_Position = position.xyww;
}