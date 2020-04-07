#version 330

out vec4 colour;

in vec4 vColour;
in vec2 texCoord;

struct ambientLight
{
	vec3 colour;
	float ambientIntensity;
};


uniform sampler2D textureSample;
uniform ambientLight ambLight;


void main()
{
	vec4 ambientColour = vec4(ambLight.colour, 1.0f) * ambLight.ambientIntensity;

	colour = texture(textureSample, texCoord) * vColour * ambientColour;
}