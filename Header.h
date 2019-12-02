#pragma once
#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

void processInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition);

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

const float TO_RADIANS = (float)(3.1415926535897 / 180);
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

const glm::vec3 cubePositions[] =
{

	glm::vec3(0.0f, 0.0f, 2.0f),
	glm::vec3(1.0f, 0.0f, 2.0f),
	glm::vec3(2.0f, 0.0f, 2.0f),
	glm::vec3(-1.0f, 0.0f, 2.0f),
	glm::vec3(-2.0f, 0.0f, 2.0f),
	glm::vec3(-3.0f, 0.0f, 2.0f),
	glm::vec3(-3.0f, 0.0f, 1.0f),
	glm::vec3(2.0f, 0.0f, 1.0f),
	

	glm::vec3(2.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 0.0f, -1.0f),
	glm::vec3(2.0f, 0.0f, -2.0f),

	glm::vec3(-3.0f, 0.0f, 0.0f),
	glm::vec3(-3.0f, 0.0f, -1.0f),
	glm::vec3(-3.0f, 0.0f, -2.0f),
	glm::vec3(-3.0f, 0.0f, -3.0f),

	glm::vec3(-3.0f, 0.0f, -4.0f),
	glm::vec3(-2.0f, 0.0f, -5.0f),
	glm::vec3(-1.0f, 0.0f, -6.0f),
	glm::vec3(0.0f, 0.0f, -7.0f),
	glm::vec3(1.0f, 0.0f, -8.0f),
	glm::vec3(2.0f, 0.0f, -8.0f),
	glm::vec3(3.0f, 0.0f, -8.0f),

	/*glm::vec3(-1.0f, 0.0f, -1.0f),
	glm::vec3(-3.0f, 0.0f, -2.0f),
	glm::vec3(-2.0f, 0.0f, -4.0f),
	glm::vec3(0.0f, 0.0f, -6.0f),
	glm::vec3(-3.0f, 0.0f, -7.0f),
	glm::vec3(-1.0f, 0.0f, -8.0f),
	glm::vec3(2.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 0.0f, -5.0f),
	glm::vec3(3.0f, 0.0f, -3.0f),
	glm::vec3(2.0f, 0.0f, -8.0f)*/
};