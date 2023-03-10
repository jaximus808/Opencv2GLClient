#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<iomanip>
#include"SerialPort.h"
#include<string>
#include<glm/glm.hpp>
#include<opencv2/opencv.hpp>
#include<thread>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include"GameManager.h"
#include"Packet.h"
#include"glext.h"
//use define later


void getCameraInput(cv::VideoCapture *cap, cv::Mat *frame, bool *backChanged, bool *cvCapture)
{
	while (*cvCapture)
	{
		if (!(*backChanged) )
		{
			*cap >> *frame;
			*backChanged = true; 
		}
	}
}


// Vertex Shader source code
unsigned char* cvMat2TexInput(cv::Mat& img)
{
	cvtColor(img, img, cv::COLOR_BGR2RGB);
	flip(img, img, -1);
	return img.data;
}

int main()
{
	char inputData[20];
	//double oldFreq = 60.0;



	std::vector<Packet> packetQueue;
	bool listeningToServer = true;

	cv::VideoCapture cap(0);
	cv::Mat frame;
	bool backgroundChanged = false;
	bool cvCapture = true; 
	bool connectedToServer = false; 


	int width = 1200; 
	int height = 1200;
	float rotation = 0.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GameManager gameManager("127.0.0.1", 8000, "default.vert", "default.frag", width, height, glm::vec3(0.0f, 0.0f, 2.0f), "Client");

	//gameManager.CreateClient(0, glm::vec3(-25.5f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	Shader backgroundShader("background.vert", "background.frag");
	// Vertices coordinates


	Vertex lightVertices[] =
	{ //     COORDINATES     //
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
	
	GLfloat bgvertices[] =
	{
		 -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left
		1.0f,   1.0f, 0.0f, 1.0f, 1.0f, // top right
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // below left
		1.0f,  -1.0f, 0.0f, 1.0f, 0.0f  // below right 


	};
	GLuint bgindices[] =
	{
		0, 1, 2,
		1, 2, 3
		 // Upper triangle
	};
	//GLFWwindow* window = glfwCreateWindow(width, height, "Client", NULL, NULL);

	GLuint bVAO, bVBO, bEBO;

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(1, &bVAO);
	glGenBuffers(1, &bVBO);
	glGenBuffers(1, &bEBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(bVAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, bVBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(bgvertices), bgvertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bEBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgindices), bgindices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




	std::cout << "FORTNITE" << std::endl;

	glm::vec4 lightColor = glm::vec4(0.8f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-0.5f, 0.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	gameManager.ActivateShader();
	glUniform4f(glGetUniformLocation(gameManager.getShaderId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(gameManager.getShaderId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::vec3 LightOrientation = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float prevTime = 0.0f;
	float currentTime = 0.0f;
	float deltaTime; 
	glEnable(GL_DEPTH_TEST);

	//Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), window);

	//Model model("Model/sword/scene.gltf",shaderProgram, camera, glm::vec3(-25.0f, 0.0f, 0.0f));
	//Client client(0,"Model/sword/scene.gltf", shaderProgram, camera, glm::vec3(-25.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	bool recalcLightPos = false;
	float lightSpeed = 0.4f;

	cap >> frame; 
	unsigned char* image = cvMat2TexInput(frame);

	unsigned int frameW = frame.rows;
	unsigned int frameH = frame.cols;

	unsigned int bgtexture;
	glGenTextures(1, &bgtexture);
	glBindTexture(GL_TEXTURE_2D, bgtexture); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0); 

	GLuint tex0Uni = glGetUniformLocation(backgroundShader.ID, "bgTex");
	backgroundShader.Activate();
	glUniform1i(tex0Uni, 0);

	std::cout << "WTF?" << std::endl;

	std::thread cvThread(getCameraInput, &cap, &frame, &backgroundChanged, &cvCapture );

	gameManager.StartRecieve(&packetQueue, &listeningToServer);

	//Packet packet;

	//packet.Write(5);

	//gameManager.SendData(packet);

	gameManager.ConnectToMeta();
	while (!glfwWindowShouldClose(gameManager.getWindow()))
	{
		/*if (packetQueue.size() > 0)
		{
			gameManager.handlePacket();
		}*/
		/*cap >> frame;
		image = cvMat2TexInput(frame);*/

		if (packetQueue.size() > 0)
		{
			std::cout << packetQueue[0].size() << std::endl;
			gameManager.handlePacket(&packetQueue[0]);
			std::cout << packetQueue[0].size()<<std::endl;
			packetQueue.erase(packetQueue.begin());
		}
		if (backgroundChanged)
		{
			if (frame.empty())
			{
				std::cout << "Cannot open video capture device" << std::endl;
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, bgtexture);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, frameW, frameH, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
				glGenerateMipmap(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
				backgroundChanged = false;
			}

		}

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cap >> frame;

		//draw background 
		

		glDisable(GL_DEPTH_TEST);
		backgroundShader.Activate();
		glBindTexture(GL_TEXTURE_2D, bgtexture);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(bVAO);
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glEnable(GL_DEPTH_TEST);
		currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		gameManager.UpdateFrame(deltaTime);

		
		glfwSwapBuffers(gameManager.getWindow());
		glfwPollEvents();

	}
	std::cout << "program ended" << std::endl;
	listeningToServer = false;
	cvCapture = false;
	gameManager.EndRecieve();
	cvThread.join();
	gameManager.endProgram();
	backgroundShader.Delete();
	glDeleteVertexArrays(1, &bVAO);
	glDeleteBuffers(1, &bVBO);
	glDeleteBuffers(1, &bEBO);
	//waits for the cvInput to end;
	return 0; 
}