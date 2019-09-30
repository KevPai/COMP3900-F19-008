#include "Header.h"

// Process user inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	//If escape key is pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
		//model = glm::translate(model, glm::vec3(0.5f, 1.0f, 0.0f));
}
