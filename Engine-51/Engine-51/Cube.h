#pragma once
#include "Header.h"
class Cube {
public:
	Cube()
	{
		model = glm::mat4(1.0f);
	}	

	glm::mat4 getModel()
	{
		return model;
	}

	void move(glm::vec3 position)
	{
		model = glm::translate(model, position);
		x = position.x;
		y = position.y;
		z = position.z;
	}

	void rotate(glm::vec3 rotate, glm::vec3 axis)
	{
		model = glm::rotate(model, glm::radians(rotate.y), axis);
	}

	glm::vec3 init(glm::vec3 vec) {
		initPos = vec;
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return initPos;
	}
	glm::vec3 getPos() {
		return glm::vec3(x, y, z);
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
private:
	float x = 0.0f, y = 0.0f, z = 0.0f;
	glm::mat4 model;
	glm::vec3 initPos = glm::vec3 (0.0f);	
};