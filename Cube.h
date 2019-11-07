#pragma once
#include "Header.h"

class Cube {
public:
	Cube()
	{
		model = glm::mat4(1.0f);
	}
	glm::mat4 getModel();
	void move(glm::vec3);
	void rotate(glm::vec3, glm::vec3);
	float getX();
	float getY();
	float getZ();
private:
	float x = 0.0f, y = 0.0f, z = 0.0f;
	glm::mat4 model;
};