#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "InputComponent.h"

struct CameraComponent
{
	CameraComponent() = default;

	CameraComponent(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, float velocity, float turnSpeed)
		: m_position(position)
		, m_front(glm::vec3(0.0f, 0.0f, -1.0f))
		, m_worldUp(worldUp)
		, m_yaw(yaw)
		, m_pitch(pitch)
		, m_velocity(velocity)
		, m_turnSpeed(turnSpeed)
	{
		Update();
	}

	glm::mat4 CalculateViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Update()
	{
		m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(m_front);

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

	void UpdateInput(InputComponent& input, float deltaTime)
	{
		InputDirectionFlags directionFlags = input.GetDirection();
		if (directionFlags.Forwards)
		{
			MoveForwards(deltaTime);
		}
		if (directionFlags.Backwards)
		{
			MoveBackwards(deltaTime);
		}
		if (directionFlags.Left)
		{
			MoveLeft(deltaTime);
		}
		if (directionFlags.Right)
		{
			MoveRight(deltaTime);
		}

		MouseControl(input.GetMouseChange(), deltaTime);

		Update();
	}

	void MoveForwards(float deltaTime)
	{
		m_position += m_front * (m_velocity * deltaTime);
	}

	void MoveBackwards(float deltaTime)
	{
		m_position -= m_front * (m_velocity * deltaTime);
	}

	void MoveLeft(float deltaTime)
	{
		m_position -= m_right * (m_velocity * deltaTime);
	}

	void MoveRight(float deltaTime)
	{
		m_position += m_right * (m_velocity * deltaTime);
	}

	void MouseControl(sf::Vector2i mouseDelta, float deltaTime)
	{
		mouseDelta.x *= (int)m_turnSpeed;
		mouseDelta.y *= (int)m_turnSpeed;

		m_yaw -= mouseDelta.x * deltaTime;
		m_pitch += mouseDelta.y * deltaTime;

		if (m_pitch > 89.0f)
		{
			m_pitch = 89.0f;
		}

		if (m_pitch < -89.0f)
		{
			m_pitch = -89.0f;
		}
	}

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