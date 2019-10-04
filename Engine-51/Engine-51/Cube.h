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
	}

	void rotate(glm::vec3 rotate, glm::vec3 axis) 
	{
		model = glm::rotate(model, glm::radians(rotate.y), axis);
	}

private:
	glm::mat4 model;
};