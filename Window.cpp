#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Collision.h"
#include "LoadTexture.h"
#include "Plane.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

ImVector<char*> chat;
float scale = 0.01f;
double lastX = SCR_WIDTH / 2.0f;
double lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
const char* glsl_version = "#version 330";


//Holds position of object
glm::vec3 position(0.0f);

//Holds rotation of object
glm::vec3 rotation(0.0f, 270.0f, 0.0f);

//Holds camera position
glm::vec3 camPosition = glm::vec3(0.0f);

Camera camera(position);

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

	#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
		bool err = gl3wInit() != 0;
	#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
	#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
		bool err = gladLoadGL() == 0;
	#else
		bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
	#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsDark();
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//Set mouse movement
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	Cube cubes[10];
	Plane myPlane;

	//Load and create a texture 
	unsigned int texture[3];
	glGenTextures(3, texture);

	//All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	//Load and create a texture 
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	LoadTexture crate("crate.jpg");

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	LoadTexture grassHill("StoneBlock.png");

	//Load and create a texture 
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	LoadTexture tank("Models/Tank_dif.jpg");

	GLchar modelPath[] = "Models/Tank.obj";
	Model ourModel(modelPath);

	cout << "Left: " << ourModel.getDimX()[0]*scale << ",Right: " << ourModel.getDimX()[1]*scale << endl;	
	cout << "Front: " << ourModel.getDimZ()[0]*scale << ",Back: " << ourModel.getDimZ()[1]*scale << endl;

	bool show_Fps = true;

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (show_Fps)
		{
			ImGui::SetNextWindowBgAlpha(0.35f);
			ImGui::Begin("FPS", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
			ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
			ImGui::End();
		}
		if (show_Fps) {
			ImGui::Begin("HUD", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(0.0, 600), 1);
			ImVec2 x = ImVec2(-100.0, 50.0), y = ImVec2(20.0, 20.0);
			ImGui::Text("Insert Username Here");
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
			ImGui::ProgressBar(1.0, x, NULL);
			ImGui::PopStyleColor();
			ImGui::End();
		}

		if (show_Fps) {
			char buffer[128];
			memset(buffer, 0, sizeof(buffer));
			ImGui::Begin("Chat", NULL, 0);
			if (ImGui::InputText("Chat Input", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
				char* s = buffer;
				chat.push_back(_strdup(s));
			}
			for (int i = 0; i < chat.size(); i++) {
				ImGui::Text(chat[i]);
			}
			ImGui::End();
		}

		// Checks inputs
		processInput(window, position, rotation, camPosition);		

		// Rendering...
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Window color
		glClear(GL_COLOR_BUFFER_BIT);

		//Clears out repeating sides so cube looks correct on rotation
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use shader and vertex array
		myShader.Use();

		//A virtual camera to see 3D objects
		glm::mat4 projection = glm::mat4(1.0f);
		//Handles field of view, aspect ratio, 'near-clipping plane', and 'far-clipping plane'
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);		

		//Moves the view
		glm::mat4 view = camera.GetViewMatrix();
		view = glm::translate(view, camPosition);
		view = glm::translate(view, glm::vec3(0.0f, -0.8f, 0.0f));

		//Gets the locations of out matrixes
		unsigned int modelLoc = glGetUniformLocation(myShader.Program, "model");
		unsigned int viewLoc = glGetUniformLocation(myShader.Program, "view");
		//Pass to shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		//Sets projection onto shader
		myShader.setMat4("projection", projection);

		cubes->bindArray();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		vector<int> cubeL;
		float dist = 2.0f;

		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].draw();
			glm::scale(cubes[i].getModel(), glm::vec3(2.0f));
			cubes[i].move(cubePositions[i]);

			if (abs(cubePositions[i].x - position.x) <= dist) {
				if (abs(cubePositions[i].z - position.z) <= dist)
					cubeL.push_back(i);
			}

			myShader.setMat4("model", cubes[i].getModel());			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
    
		myPlane.bindArray();
		myPlane.draw();
		myShader.setMat4("model", myPlane.getModel());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		float pushback = 0.015f;

		for (int i : cubeL) {
			switch (checkCollision(ourModel, position, cubes[i], scale)) {
			case 3:
				position.z -= pushback;
				camPosition.z += pushback;
				break;
			case -3:
				position.z += pushback;
				camPosition.z -= pushback;
				break;
			case 1:
				position.x -= pushback;
				camPosition.x += pushback;
				break;
			case -1:
				position.x += pushback;
				camPosition.x -= pushback;
				break;
			case 0:
				break;
			}
		}

		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); // translate it down so it's at the center of the scene		
		model = glm::translate(model, glm::vec3(position));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));	// it's a bit too big for our scene, so scale it down

		myShader.setMat4("model", model);
		ourModel.Draw(myShader);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
	}

	//Clean up objects
	cubes->cleanUp();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Clean out GFLW on close
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = (float) (xpos - lastX);
	float yoffset = (float) (lastY - ypos); // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(-xoffset, -yoffset/2);
}