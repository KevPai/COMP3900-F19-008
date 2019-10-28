#pragma once
#include "Header.h"

//Sesitivity of mouse
const GLfloat SENSITIVITY = 0.01f;

class Camera {
public:
	//Constructor for vectors
	Camera(glm::vec3 position) {

		this->objectPosition = position;
		this->camPosition = glm::vec3(position.x, position.y, position.z);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->mouseSensitivity = SENSITIVITY;
		this->theta = 0;
		this->phi = 0;

		this->updateCameraVectors();
	}

	//Look at an object
	glm::mat4 GetViewMatrix()
	{
		glm::mat4 view = glm::lookAt(this->camPosition, this->objectPosition, this->up);

		return view;
	}

	//Process mouse movement for camera
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;

		this->theta += xOffset;
		this->phi += yOffset;

		//Prevents user from moving camera out of bounds
		if (constrainPitch)
		{
			if (this->phi > 89.0f)
			{
				this->phi = -89.0f;
			}
			if (this->phi < 0.0f)
			{
				this->phi = 0.0f;
			}
		}

		this->updateCameraVectors();
	}

private:
	glm::vec3 camPosition;
	glm::vec3 objectPosition;
	glm::vec3 up;

	GLfloat theta;
	GLfloat phi;

	GLfloat mouseSensitivity;

	void updateCameraVectors()
	{
		this->camPosition.y = -6.0f * sin(this->phi);
		float zx = -6.0f * cos(this->phi);
		this->camPosition.x = zx * sin(this->theta);
		this->camPosition.z = zx * cos(this->theta);
	}
};