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
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int heigh) {
	glViewport(0, 0, width, heigh);
	std::cout << "width:" << width << " heigh:" << heigh << std::endl;
}

unsigned int loadTexture(char const* path) {
	unsigned int textureId;
	glGenTextures(1, &textureId);
	int width, heigh, nrComponents;
	unsigned char* data = stbi_load(path, &width, &heigh, &nrComponents, 0);
	if (data) {
		GLenum formate = GL_RGB;
		if (nrComponents == 1) {
			formate = GL_RED;
		}
		else if (nrComponents == 3) {
			formate = GL_RGB;
		}
		else if (nrComponents == 4) {
			formate = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, formate, width, heigh, 0, formate, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, formate == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, formate == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureId;
}


int main() {

	int width = 1280;
	int heigh = 674;
	Window* window = new Window("Shader", width, heigh);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, heigh);
	Shader* shader = new Shader("./vshader.glsl", "./fshader.glsl");
	int success = shader->compile();
	if (!success) {
		std::cout << "COMPILE SHADER ERROR:" << shader->getInfoLog() << std::endl;
		delete window;
		return -2;
	}

	unsigned int texture = loadTexture("banner.png");

	float vPoint[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPoint), vPoint, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!window->shouldClose()) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float time = Window::getTime();

		shader->setUniform("time", time);
		shader->setUniform("texture1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		shader->useProgram();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window->swapBuffers();
		Window::pollEvents();
	}
	delete window;
	delete shader;
	return 0;
}

