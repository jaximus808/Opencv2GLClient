#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
//#include<opencv2/opencv.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include"GameManager.h"
#include"Packet.h"
//use define later

// Vertex Shader source code

int main()
{
	
	int width = 1200; 
	int height = 1200;
	float rotation = 0.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Vertices coordinates

	/*0, 1, 2,
		0, 2, 3,

		0, 1, 5,
		0, 4, 5,

		1, 2, 6,
		1, 5, 6,

		2, 3, 7,
		2, 6, 7,

		3, 0, 4,
		3, 7, 4,

		4, 5, 6,
		4, 6, 7,*/

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
	

	//GLFWwindow* window = glfwCreateWindow(width, height, "Client", NULL, NULL);

	//cv::VideoCapture cap(0);
	//cv::Mat frame;
	
	GameManager gameManager("127.0.0.1",8000, "default.vert", "default.frag", width, height, glm::vec3(0.0f, 0.0f, 2.0f),"Client");

	gameManager.CreateClient(0, glm::vec3(-25.5f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	Packet packet;

	packet.Write(5);

	gameManager.SendData(packet);


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
	float lightSpeed = 0.4f;;
	while (!glfwWindowShouldClose(gameManager.getWindow()))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //set it 
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear buffer of back color information


		currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		gameManager.UpdateFrame(deltaTime);
		/*camera.Inputs(deltaTime);

		camera.updateMatrix(45.0f, 0.1f, 1000000.0f);
		client.moveClientState(glm::vec3(-0.5f* deltaTime,0.0f, 0.0f), glm::vec3(10.0f * deltaTime, 0.0f, 0.0f));
		client.Draw();*/
		//glBindVertexArray(VAO);
;
		glfwSwapBuffers(gameManager.getWindow());
		glfwPollEvents();

	}
	
	gameManager.endProgram();

	return 0; 
}