#pragma once
#include "Shaders/Shader.h"
#include "Textures/LoadTexture.h"
#include "Objects/Plane.h"
#include "Skybox/Skybox.h"
#include "Input/Camera.h"
#include "Physics/Collision.h"
#include "AI/TankAI.h"
#include "GUI/imgui.h"
#include "GUI/imgui_impl_glfw.h"
#include "GUI/imgui_impl_opengl3.h"
#include "Networking/Client.h"
#include <thread>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#include <list>

//chat vector
ImVector<char*> chat;

//vectors for model, position, rotation
vector<glm::mat4> playerModel;
vector<int> playerId;
vector<glm::vec3> playerPosition;
vector<glm::vec3> playerRotation;
glm::vec3 tempPos;
glm::vec3 tempRot;
bool chatMode;

float scale = 0.01f;
double lastX = SCR_WIDTH / 2.0f;
double lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
const char* glsl_version = "#version 330";

//Server Stuff
Client client;
thread readthread, writethread;
char username[50];

//Player stuff
int playerNumber;
int playerCount;

//Holds position of object
glm::vec3 position(0.0f);
//Holds rotation of object
glm::vec3 rotation(0.0f, 270.0f, 0.0f);

//Holds camera position
glm::vec3 camPosition = glm::vec3(0.0f);
Camera camera(position);

void readFunc() {
	glm::vec3 playerPos(0.0f);
	glm::vec3 playerRot(0.0f, 90.0f, 0.0f);
	//while the client is running the server will continue to listen to messages
	while (client.isClientRunning) {

		//variables for handling messages
		char message[256];

		//actual packet received from either client or server

		string update = client.updatePos();
		stringstream ss(update);
		string encode;
		size_t pos = 0;
		ostringstream oss;
		int id;
		float posx, posy, posz, rotx, roty, rotz;
		char* s;
		int code = 0;
		ss >> code;
		if (!update.empty()) //checks if the packet is empty
		{

			switch (code) {

			case 0: //login message
				encode = update.substr(update.find(" ") + 1);
				memset(message, 0, sizeof(message));
				strcpy_s(message, encode.c_str());
				cout << encode << endl;
				s = message;
				chat.push_back(_strdup(s));

				if (client.isserver()) {

					//add new player information to server
					cout << "spawning new player" << endl;
					playerCount++;
					playerId.push_back(playerCount);
					playerPosition.push_back(playerPos);
					playerRotation.push_back(playerRot);
					glm::mat4 tank;
					playerModel.push_back(tank);
					//assign player information
					oss << 3 << " " << playerCount;
					cout << oss.str() << endl;
					client.BroadCastMessageToAll(oss.str()); //send new player information to other clients and spawn in player

					for (int i = 0; i < playerId.size(); i++) //new player is sent information on itself and the current players in the game
					{
						oss.str("");
						oss << 4 << " " << playerId[i] << " " << playerPosition[i].x << " " << playerPosition[i].y << " " << playerPosition[i].z
							<< " " << playerRotation[i].x << " " << playerRotation[i].y << " " << playerRotation[i].z;
						client.BroadCastMessageToAll(oss.str());
					}
				}
				break;
			case 1: //messages for chat
				encode = update.substr(update.find(" ") + 1);
				memset(message, 0, sizeof(message));
				strcpy_s(message, encode.c_str());
				cout << encode << endl;
				s = message;
				chat.push_back(_strdup(s));
				break;

			case 3: //sent player info |3|PlayerNumber|
				encode = update.substr(update.find(" ") + 1);
				if (playerNumber == NULL) {
					playerNumber = stoi(encode);
				}
				break;

			case 4: //initialize positions in clients
				encode = update.substr(update.find(" " + 1));
				ss.str("");
				ss.str(encode);
				ss >> id >> posx >> posy >> posz >> rotx >> roty >> rotz;
				//cout << ss.str() << endl;
				//cout << id << posx << posy << posz << rotx << roty << rotz;s
				glm::vec3 position;
				glm::vec3 rotation;
				glm::mat4 tank;
				position.x = posx;
				position.y = posy;
				position.z = posz;
				rotation.x = rotx;
				rotation.y = roty;
				rotation.z = rotz;
				playerId.push_back(id);
				playerModel.push_back(tank);
				playerPosition.push_back(position);
				playerRotation.push_back(rotation);
				break;
			case 5: //update position 4 playerid position rotation
				encode = update.substr(update.find(" ") + 1);
				ss.str("");
				ss.str(encode);
				ss >> id >> posx >> posy >> posz >> rotx >> roty >> rotz;
				playerPosition[id].x = posx;
				playerPosition[id].y = posy;
				playerPosition[id].z = posz;

				playerRotation[id].x = rotx;
				playerRotation[id].y = roty;
				playerRotation[id].z = rotz;
				break;
			}

		}
	}
}

void mainThread()
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
	}

	//Size of rendering window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//Need this so cube sides do not draw over each other
	glEnable(GL_DEPTH_TEST);

	//Instantiate object shaders
	Shader myShader("Shaders/core.vs", "Shaders/core.frag");
	//Instantiate skybox shaders
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.frag");

	//Load and bind graphic objects
	const int cubeSize = sizeof(cubePositions) / sizeof(cubePositions[0]);
	Cube cubes[cubeSize];
	Plane myPlane;
	Skybox mySkybox;

	//Load and create a texture 
	unsigned int texture[3];
	glGenTextures(3, texture);

	//All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	//Load crate texture from path
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	LoadTexture crate("Textures/crate.jpg");
	
	//Load plane texture from path
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	LoadTexture grassHill("Textures/StoneBlock.png");

	//Load tank texture from path
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	LoadTexture tank("Textures/Tank_dif.jpg");

	//Load skybox texture from six paths
	vector<string> faces;
	faces.push_back("Textures/skybox_right.jpg");
	faces.push_back("Textures/skybox_left.jpg");
	faces.push_back("Textures/skybox_top.jpg");
	faces.push_back("Textures/skybox_bottom.jpg");
	faces.push_back("Textures/skybox_front.jpg");
	faces.push_back("Textures/skybox_back.jpg");
	unsigned int cubemapTexture = mySkybox.loadCubemap(faces);

	//Load tank model from path
	GLchar modelPath[] = "Models/Tank.obj";
	Model ourModel(modelPath);

	cout << "Left: " << ourModel.getDimX()[0]*scale << ",Right: " << ourModel.getDimX()[1]*scale << endl;	
	cout << "Front: " << ourModel.getDimZ()[0]*scale << ",Back: " << ourModel.getDimZ()[1]*scale << endl;

	bool show_Fps = true;
	//server fills up spot of player list
	if (client.isserver()) {
		playerNumber = 0;
		playerCount = 0;
		playerId.push_back(playerNumber);
		glm::vec3 pos(0.0f);
		playerPosition.push_back(pos);
		glm::vec3 rot(0.0f, 90.0f, 0.0f);
		playerRotation.push_back(rot);
		glm::mat4 player;
		playerModel.push_back(player);
	}

	//login message for the host and other clients
	if (!client.isserver()) {
		char lmessage[256];
		strcpy_s(lmessage, "0 ");
		strcat_s(lmessage, username);
		strcat_s(lmessage, " Has joined the game.");
		client.sendMessage(_strdup(lmessage));
	}

	// Src and dest may be changed to different position in the area
	TankAI tankAI(31, 31, cubeSize);
	glm::vec3 src = glm::vec3(0.0f, 0.0f, 0.0f); // Based on the position of the tank
	glm::vec3 dest = glm::vec3(4.0f, 0.0f, -6.0f);
	
	tankAI.performSearch(position, rotation, src, dest);
	int move = 1;

	// Adjust movements to create offset from cubes so tank doesn't get stuck
	cout << "Offsetting path..." << endl;
	tankAI.adjustMovements();
	tankAI.printMovements();

	// Get the movements
	vector<pair<int, int>> movements = tankAI.getMovements();

	//Configure shaders
	myShader.Use();
	myShader.setInt("textures", 0);

	skyboxShader.Use();
	skyboxShader.setInt("skybox", 0);

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
			ImGui::Text(username);
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
			ImGui::ProgressBar(1.0, x, NULL);
			ImGui::PopStyleColor();
			ImGui::End();
		}

		if (show_Fps) {

			char buffer[128];
			char message[256];
			char encode[256];
			memset(message, 0, sizeof(message));
			memset(buffer, 0, sizeof(buffer));

			strcpy_s(message, username);
			ImGui::Begin("Chat", NULL, 0);
			if (ImGui::InputText("Chat Input", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
				strcat_s(message, ": ");
				strcat_s(message, buffer);
				char* s = message;
				chat.push_back(_strdup(s));
				strcpy_s(encode, "1 ");
				strcat_s(encode, message);
				char* t = encode;
				if (!client.isserver())
				{
					client.sendMessage(t);
				}
				else {
					client.BroadCastMessageToAll(t);
				}
			}
			for (int i = 0; i < chat.size(); i++) {
				ImGui::Text(chat[i]);
			}
			ImGui::End();
		}

		if (playerPosition.size() != 0 && playerRotation.size() != 0) {
			tempPos = playerPosition[playerNumber];
			tempRot = playerRotation[playerNumber];
		}
		// Checks inputs
		processInput(window, playerPosition[playerNumber], playerRotation[playerNumber], camPosition);

		if (tempPos != playerPosition[playerNumber] || tempRot != playerRotation[playerNumber]) {
			ostringstream oss;
			oss << 5 << " " << playerNumber << " " << playerPosition[playerNumber].x << " " << playerPosition[playerNumber].y << " " << playerPosition[playerNumber].z
				<< " " << playerRotation[playerNumber].x << " " << playerRotation[playerNumber].y << " " << playerRotation[playerNumber].z;
			if (client.isserver()) {
				client.BroadCastMessageToAll(oss.str());
			}
			else {
				client.sendMessage(oss.str());
			}
		}

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

		//Bind cubes and cube texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		cubes->bindArray();

		std::list<int> cubeL;
		float dist = 1.5f;

		for (unsigned int i = 0; i < cubeSize; i++)      
		{
			cubes[i].draw();
			glm::scale(cubes[i].getModel(), glm::vec3(2.0f));
			cubes[i].move(cubePositions[i]);			
			if (abs(cubePositions[i].x - playerPosition[playerNumber].x) <= dist) {
				if (abs(cubePositions[i].z - playerPosition[playerNumber].z) <= dist)

					cubeL.push_back(i);
			}

			myShader.setMat4("model", cubes[i].getModel());			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//Bind plane and plane texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
    
		myPlane.bindArray();
		myPlane.draw();
		myShader.setMat4("model", myPlane.getModel());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		//Bind model and model texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		// render the loaded model
		for (int i = 0; i < playerModel.size(); i++) {
			playerModel[i] = glm::mat4(1.0f);
		}

		float pushback = 0.03f;
    
		for (int i : cubeL) {
			switch (checkCollision(ourModel, playerPosition[playerNumber], cubes[i], scale)) {          
			case 3:
				playerPosition[playerNumber].z -= pushback;
				camPosition.z += pushback;
				break;
			case -3:
				playerPosition[playerNumber].z += pushback;
				camPosition.z -= pushback;
				break;
			case 1:
				playerPosition[playerNumber].x -= pushback;
				camPosition.x += pushback;
				break;
			case -1:
				playerPosition[playerNumber].x += pushback;
				camPosition.x -= pushback;
				break;
			case 0:
				break;
			}			
		}

		for (int i = 0; i < playerModel.size(); i++) {
			//cout << i << endl;
			playerModel[i] = glm::translate(playerModel[i], glm::vec3(0.0f, -0.4f, 0.0f)); // translate it down so it's at the center of the scene		
			playerModel[i] = glm::translate(playerModel[i], glm::vec3(playerPosition[i]));
			playerModel[i] = glm::rotate(playerModel[i], glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			playerModel[i] = glm::rotate(playerModel[i], glm::radians(playerRotation[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
			playerModel[i] = glm::scale(playerModel[i], glm::vec3(scale, scale, scale));	// it's a bit too big for our scene, so scale it down

			myShader.setMat4("model", playerModel[i]);
			ourModel.Draw(myShader);
		}

		// Iterate through movements to move the AI controlled tank until it reaches final movement
		// This is disabled because this functionality was not integrated
		//tankAI.move(movements, move, position, rotation);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Finally draw skybox
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);

		//Define skybox cube
		mySkybox.bindArray();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

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
}

int main() {

	std::cout << "Enter User Name" << endl;
	std::cin >> username;
	std::cout << " \"Join\" or \"Host\"" << endl;
	string message;
	std::cin >> message;
	if (message == "host") {
		client.createServer();
		writethread = thread(mainThread);
		readthread = thread(readFunc);
	}
	else if (message == "join")
	{
		std::cout << "Enter ip address of host" << endl;
		string ip;
		std::cin >> ip;
		client.createClient(ip);
		writethread = thread(mainThread);
		readthread = thread(readFunc);
	}
	readthread.join();
	writethread.join();

	return 0;
}

//Proccess mouse movement for camera
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