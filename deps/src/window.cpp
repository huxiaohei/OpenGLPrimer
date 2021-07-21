/*****************************************************************
* Description ´°¿Ú
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 Áõ»¢
****************************************************************/

#include <iostream>
#include <window/window.h>

Window::Window(const char* title, int width, int heigh) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, heigh, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "CREATE GLFW WINDOW FAIL" << std::endl;
		glfwTerminate();
	}
	else {
		std::cout << "CRAETE GLFW WINDOW SUCCESS" << std::endl;
	}
}

void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
	glfwSetFramebufferSizeCallback(window, callback);
}

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(window);
}

void Window::setShouldClose(bool close) {
	glfwSetWindowShouldClose(window, close);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

float Window::getTime() {
	return glfwGetTime();
}

void Window::pollEvents() {
	glfwPollEvents();
}

Window::~Window() {
	glfwTerminate();
}

