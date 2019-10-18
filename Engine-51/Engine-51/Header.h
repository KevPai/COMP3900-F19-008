#pragma once
#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

<<<<<<< HEAD
int processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition);
=======
void processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition);

//void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
>>>>>>> Kevin-branch

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
