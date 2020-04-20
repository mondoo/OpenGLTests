#pragma once

#include <string>

#include "engine/Global.h"

constexpr float toRadians = 3.14159265f / 180.0f;

namespace Utilities
{
	const std::string FPS()
	{
		return std::to_string((int)(1.f / Global::GetDeltaTime())) + "FPS";
	}

	void Rotate(float& currentRotation, float amountToRotate)
	{
		currentRotation += 60.0f * Global::GetDeltaTime();
		if (currentRotation >= 360.f)
		{
			currentRotation = 0.0f;
		}
	}

	float ToRadians(float rotation)
	{
		return rotation * toRadians;
	}
}