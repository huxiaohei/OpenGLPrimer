/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on
 * Copyright (c) 2021 Αυ»Ά
 ****************************************************************/


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "width: " << width << "height: " << height << std::endl;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	std::cout << "Create Window" << std::endl;
	glfwInit();
	// set OpenGL major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// set OpenGL minor version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// set OpenGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	GLFWwindow *window = glfwCreateWindow(800, 600, "Create Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "create window fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	// tell glfw to make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// initialize GLAD before we call any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return -2;
	}
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glViewport(0, 0, 800, 600);

	// render loop
	while (!glfwWindowShouldClose(window)) 	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}