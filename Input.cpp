#pragma once
#include "Header.h"

// Process user inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition)
{
	//If escape key is pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z += 0.005f * sinf(rotation.y * TO_RADIANS);
		position.x -= 0.005f * cosf(rotation.y * TO_RADIANS);

		camPosition.z -= 0.005f * sinf(rotation.y * TO_RADIANS);
		camPosition.x += 0.005f * cosf(rotation.y * TO_RADIANS);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z -= 0.005f * sinf(rotation.y * TO_RADIANS);
		position.x += 0.005f * cosf(rotation.y * TO_RADIANS);

		camPosition.z += 0.005f * sinf(rotation.y * TO_RADIANS);
		camPosition.x -= 0.005f * cosf(rotation.y * TO_RADIANS);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		rotation.y += 0.20f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		rotation.y -= 0.20f;
	}
	
}
