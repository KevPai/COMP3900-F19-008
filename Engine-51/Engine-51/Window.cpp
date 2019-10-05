#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "Collision.h"

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

int main()
{
	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine 51", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLAD, GLAD manages function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Size of rendering window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//Need this so cube sides do not draw over each other
	glEnable(GL_DEPTH_TEST);

	Shader myShader("core.vs", "core.frag");

	//3D Shape coordinates
	float vertices[] =
	{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] =
	{
	 glm::vec3(-1.0f, 0.0f, 1.0f),
	 glm::vec3(-3.0f, 0.0f, 2.0f),
	 glm::vec3(-2.0f, 0.0f, 4.0f),
	 glm::vec3(0.0f, 0.0f, 6.0f),
	 glm::vec3(-3.0f, 0.0f, 7.0f),
	 glm::vec3(-1.0f, 0.0f, 8.0f),
	 glm::vec3(2.0f, 0.0f, 0.0f),
	 glm::vec3(2.0f, 0.0f, 5.0f),
	 glm::vec3(3.0f, 0.0f, 3.0f),
	 glm::vec3(2.0f, 0.0f, 8.0f)
	};

	// For movement & rotation
	glm::vec3 position(0.0f);
	glm::vec3 rotation(0.0f);

	//Holds camera position
	glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, -5.0f);

	//Vertex buffer object AND vertex array object
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind vertex
	glBindVertexArray(VAO);

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Load and create a texture 
	unsigned int texture;

	//Load image, create texture and generate mipmaps
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("doge.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//Free image data
	stbi_image_free(data);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{		
		//Initialize the models
		Cube cube1;
		Cube test;

		// Checks inputs direction
		int direction = processInput(window, position, rotation, camPosition);								

		// Rendering...
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Window color
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use shader and vertex array
		myShader.Use();

		//Handles field of view, aspect ratio, 'near-clipping plane', and 'far-clipping plane'
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view;

		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);		
		view = camera.GetViewMatrix();
		view = glm::translate(view, camPosition);

		//Gets the locations of out matrixes
		unsigned int modelLoc = glGetUniformLocation(myShader.Program, "model");
		unsigned int viewLoc = glGetUniformLocation(myShader.Program, "view");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube1.getModel()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		//Sets projection onto shader
		myShader.setMat4("projection", projection);
		glBindVertexArray(VAO);

		// Adding a static cube (not moving)
		test.move(test.init(cubePositions[0]));
		myShader.setMat4("model", test.getModel());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Assigning player's cube to the movement vector, then changing the vector
		cube1.move(position);
		switch (checkCollision(cube1, test, direction)) {
		case 3:
			position.z = test.getZ() + 1.0f;
			break;
		case -3:
			position.z = test.getZ() - 1.0f;
			break;
		case 2:
			position.y = test.getY() + 1.0f;
			camPosition.y = -cube1.getY();			
			break;
		case -2:
			position.y = test.getY() - 1.0f;
			camPosition.y = -cube1.getY();
			break;
		case -1:			
			position.x = test.getX() - 1.0f;
			camPosition.x = -cube1.getX();
			break;
		case 1:
			position.x = test.getX() + 1.0f;
			camPosition.x = cube1.getX();
			break;
		case 0:
			break;
		}
		cube1.rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		myShader.setMat4("model", cube1.getModel());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		/*Cube cubes[10];
		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].move(cubes[i].init(cubePositions[i]));

			// testing on the second cube			
			checkCollision(cube1, cubes[1]);

			myShader.setMat4("model", cubes[i].getModel());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Clean up objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//Clean out GFLW on close
	glfwTerminate();
	return 0;
}
