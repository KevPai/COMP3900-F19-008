#pragma once
#include "../Header.h"
#define speed 0.03f
// Process user inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition)
{
	//If escape key is pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		rotation.y += 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		rotation.y -= 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z += speed * sinf(rotation.y * TO_RADIANS);
		position.x -= speed * cosf(rotation.y * TO_RADIANS);

		camPosition.z -= speed * sinf(rotation.y * TO_RADIANS);
		camPosition.x += speed * cosf(rotation.y * TO_RADIANS);		
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z -= speed * sinf(rotation.y * TO_RADIANS);
		position.x += speed * cosf(rotation.y * TO_RADIANS);

		camPosition.z += speed * sinf(rotation.y * TO_RADIANS);
		camPosition.x -= speed * cosf(rotation.y * TO_RADIANS);		
	}	
}
