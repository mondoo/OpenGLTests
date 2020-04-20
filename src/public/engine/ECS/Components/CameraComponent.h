#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <SFML/System/Vector2.hpp>

struct InputComponent;

struct CameraComponent
{
	CameraComponent() = default;

	CameraComponent(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, float velocity, float turnSpeed);

	glm::mat4 CalculateViewMatrix();

	void Update();

	void UpdateInput(InputComponent& input, float deltaTime);

	void MoveForwards(float deltaTime);

	void MoveBackwards(float deltaTime);

	void MoveLeft(float deltaTime);

	void MoveRight(float deltaTime);

	void MouseControl(sf::Vector2i mouseDelta, float deltaTime);

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