#pragma once
#include "Header.h"

class Plane {
public:
	Plane() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void draw() {
		model = glm::mat4(1.0f);
	}

	void bindArray() {
		glBindVertexArray(VAO);
	}
	
	glm::mat4 getModel()
	{
		return model;
	}

private:
	glm::mat4 model;
	unsigned int VBO, VAO;

	float planeVertices[30] = {
		 100.0f, -0.5f,  100.0f,  2.0f, 0.0f,
		-100.0f, -0.5f,  100.0f,  0.0f, 0.0f,
		-100.0f, -0.5f, -100.0f,  0.0f, 2.0f,

		 100.0f, -0.5f,  100.0f,  2.0f, 0.0f,
		-100.0f, -0.5f, -100.0f,  0.0f, 2.0f,
		 100.0f, -0.5f, -100.0f,  2.0f, 2.0f
	};
};