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

void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
