#include "engine/gameframework/Camera.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <SFML/Window/Keyboard.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, float velocity, float turnSpeed)
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

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::UpdateKeyboard(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		MoveForwards(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		MoveLeft(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		MoveBackwards(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		MoveRight(deltaTime);
	}
}

void Camera::MouseControl(float deltaTime, sf::Vector2i mouseDelta)
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

	Update();
}

void Camera::Update()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::MoveForwards(float deltaTime)
{
	m_position += m_front * (m_velocity * deltaTime);
}

void Camera::MoveBackwards(float deltaTime)
{
	m_position -= m_front * (m_velocity * deltaTime);
}

void Camera::MoveLeft(float deltaTime)
{
	m_position -= m_right * (m_velocity * deltaTime);
}

void Camera::MoveRight(float deltaTime)
{
	m_position += m_right * (m_velocity * deltaTime);
}