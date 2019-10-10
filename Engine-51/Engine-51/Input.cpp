#include "Header.h"

// Process user inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition)
{
	//If escape key is pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//position.z += 0.03f;
		position.z += 0.03f * sinf(rotation.y * 3.14159 / 180);
		position.x -= 0.03f * cosf(rotation.y * 3.14159 / 180);

		//camPosition.z -= 0.03f;
		camPosition.z -= 0.03f * sinf(rotation.y * 3.14159 / 180);
		camPosition.x += 0.03f * cosf(rotation.y * 3.14159 / 180);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//position.z -= 0.03f;
		position.z -= 0.03f * sinf(rotation.y * 3.14159 / 180);
		position.x += 0.03f * cosf(rotation.y * 3.14159 / 180);

		//camPosition.z += 0.03f;
		camPosition.z += 0.03f * sinf(rotation.y * 3.14159 / 180);
		camPosition.x -= 0.03f * cosf(rotation.y * 3.14159 / 180);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		rotation.y += 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		rotation.y -= 1.0f;
	}
	
}
