/*****************************************************************
* Description
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 Αυ»Ά
****************************************************************/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Window/window.h>
#include <Shader/shader.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int heigh) {
	glViewport(0, 0, width, heigh);
	std::cout << "width:" << width << " heigh:" << heigh << std::endl;
}


int main() {
	
	Window *window = new Window("Shader", 800, 600);
	if (window == NULL) {
		delete window;
		return -1;
	}
	window->makeContextCurrent();
	window->setFramebufferSizeCallback(framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALIZE CLAD ERROR" << std::endl;
		delete window;
		return -2;
	}

	Shader* shader = new Shader("./vshader.glsl", "./fshader.glsl");
	int success = shader->compile();
	if (!success) {
		std::cout << "COMPILE SHADER ERROR:" << shader->getInfoLog() << std::endl;
		delete window;
		return -2;
	}
	
	float vPoint[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPoint), vPoint, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	while (!window->shouldClose()) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float time = Window::getTime();
		shader->useProgram();
		shader->setUniform("grayFactor", sin(time)/2.0f+0.5f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window->swapBuffers();
		Window::pollEvents();
	}
	delete window;
	delete shader;
	return 0;
}