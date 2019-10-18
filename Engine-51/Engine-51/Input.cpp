#include "Header.h"

// Process user inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
int processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition)
{	
	//If escape key is pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z -= 0.03f;
		camPosition.z += 0.03f;
		return 8;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z += 0.03f;
		camPosition.z -= 0.03f;
		return 2;
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		position.y -= 0.03f;
		camPosition.y += 0.03f;
		return 5;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		position.y += 0.03f;
		camPosition.y -= 0.03f;
		return 0;
	}	

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position.x -= 0.03f;
		camPosition.x += 0.03f;
		return 4;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position.x += 0.03f;
		camPosition.x -= 0.03f;
		return 6;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		rotation.y -= 1.0f;
		return 7;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		rotation.y += 1.0f;
		return 9;
	}
	return -1;
}
