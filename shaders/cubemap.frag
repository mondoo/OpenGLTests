#version 330

out vec4 colour;

in vec4 vColour;
in vec3 texCoord;

struct ambientLight
{
	vec3 colour;
	float ambientIntensity;
};

uniform samplerCube textureSample;
uniform ambientLight ambLight;

void main()
{
	vec4 ambientColour = vec4(ambLight.colour, 1.0f) * ambLight.ambientIntensity;

	colour = texture(textureSample, texCoord) * vColour * ambientColour;
}