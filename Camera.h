#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include "glm/ext.hpp"
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<glm/gtc/matrix_transform.hpp>

#include"ShaderClass.h"

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		float eulerRotX;
		float eulerRotY;

		GLFWwindow *window;
		int width;
		int height;

		bool focused = true; 

		float speed = 10.0f;
		float sensitivity = 100.0f;

		Camera(int width, int height, glm::vec3 position, GLFWwindow* window);
		Camera();

		void setPosition(glm::vec3 newPosition);

		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);

		void Inputs( float deltaTime);
};


#endif // !CAMERA_H
