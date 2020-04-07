#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include <SFML/System/Vector2.hpp>

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, float velocity, float turnSpeed);

	glm::mat4 CalculateViewMatrix();

	void UpdateKeyboard(float deltaTime);
	void MouseControl(float deltaTime, sf::Vector2i mouseDelta);

private:
	void Update();

	void MoveForwards(float deltaTime);
	void MoveBackwards(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_yaw;
	GLfloat m_pitch;

	float m_velocity;
	float m_turnSpeed;
};