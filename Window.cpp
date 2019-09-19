#include "Header.h"
#include "Shader.h"
#include "stb_image.h"

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

	Shader myShader("core.vs", "core.frag");

	//Shape coordinates
	float vertices[] =
	{
		//Position				//Color					// texture coords
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f  // top left 
	};

	unsigned int indices[] = 
	{
		0, 1, 3, //First Triangle
		1, 2, 3, //Second Triangle
	};

	//Vertex buffer object AND vertex array object
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind vertex
	glBindVertexArray(VAO);

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Bind indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Load and create a texture 
	unsigned int texture;
	//Load image, create texture and generate mipmaps
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	//All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Set texture filtering parameters
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
		// Checks inputs
		processInput(window);

		// Rendering...
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Window color
		glClear(GL_COLOR_BUFFER_BIT);

		//Use shader and vertex array
		myShader.Use();

		glBindVertexArray(VAO);
		//Draw object
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Clean up objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//Clean out GFLW on close
	glfwTerminate();
	return 0;
}