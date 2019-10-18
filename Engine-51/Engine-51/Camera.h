#pragma once
#include <vector>
#include "Header.h"

const double PI = 3.1415926535897;

//Sesitivity of mouse
const GLfloat SENSITIVITY = 0.01f;

class Camera {
public:
	//Constructor for vectors
<<<<<<< HEAD
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
		, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)
		, GLfloat yaw = YAW
		, GLfloat pitch = PITCH)
		: front(glm::vec3(0.0f, 0.0f, 1.0f))
		, movementSpeed(SPEED)
		, mouseSensitivity(SENSITIVITY)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	//Constructor for scalars
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ
		, GLfloat upX, GLfloat upY, GLfloat upZ
		, GLfloat yaw, GLfloat pitch)
		: front(glm::vec3(0.0f, 0.0f, -1.0f))
		, movementSpeed(SPEED)
		, mouseSensitivity(SENSITIVITY)
	{
		this->position = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	//Look at an object
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->front, this->up);
	}

	//Process keyboard movement for camera
	void ProcessKeyboard(Camera_Movement direction)
=======
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
>>>>>>> Kevin-branch
	{
		glm::mat4 view = glm::lookAt(this->camPosition, this->objectPosition, this->up);

<<<<<<< HEAD
		//NOT if/else OR swictch in order to move diagonally
		if (FORWARD == direction)
		{
			this->position += this->front;
		}
		if (BACKWARD == direction)
		{
			this->position -= this->front;
		}
		if (LEFT == direction)
		{
			this->position -= this->right;
		}
		if (RIGHT == direction)
		{
			this->position += this->right;
		}
=======
		return view;
>>>>>>> Kevin-branch
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
			/*if (this->theta > 89.0f)
			{
				this->theta = 89.0f;
			}
			if (this->theta < 0.0f)
			{
				this->theta = 0.0f;
			}*/

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