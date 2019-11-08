#pragma once
#include "Cube.h"

	glm::mat4 Cube::getModel()
	{
		return model;
	}

	void Cube::move(glm::vec3 position)
	{
		x = position.x;
		y = position.y;
		z = position.z;
		model = glm::translate(model, position);
	}

	void Cube::rotate(glm::vec3 rotate, glm::vec3 axis)
	{
		model = glm::rotate(model, glm::radians(rotate.y), axis);
	}

	float Cube::getX() {
		return x;
	}
	float Cube::getY() {
		return y;
	}
	float Cube::getZ() {
		return z;
	}