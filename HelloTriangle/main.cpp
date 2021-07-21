/*****************************************************************
 * Description Èý½ÇÐÎ
 * Email huxiaoheigame@gmail.com
 * Created on 2021/05/28
 * Copyright (c) 2021 Áõ»¢
 ****************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main() {\n"
"	fragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);\n"
"}\0";


GLFWwindow* createWindow(const char* title, int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "create window error" << std::endl;
		glfwTerminate();
	}
	return window;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int heigh) {
	glViewport(0, 0, width, heigh);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	std::cout << "Hello Triangle" << std::endl;
	GLFWwindow* window = createWindow("Hello Triangle", 800, 600);
	if (window == NULL) {
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "initialize glad fail" << std::endl;
		return -2;
	}
	glViewport(0, 0, 800, 600);

	// create vertex shader obj
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach the shader source code to the shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile the shader
	glCompileShader(vertexShader);
	// check compile-time errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "compile vertex shader error:" << infoLog << std::endl;
		glfwTerminate();
		return -3;
	}

	// create fragment shader obj
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach the shader source code to the shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile the shader
	glCompileShader(fragmentShader);
	// check compile-time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "compile fragment shader error:" << infoLog << std::endl;
		glfwTerminate();
		return -4;
	}

	// create shader program
	unsigned int shaderProgram = glCreateProgram();
	// attach compile shaders to the program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// link shaders
	glLinkProgram(shaderProgram);
	// check link errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "link shader program error:" << infoLog << std::endl;
		glfwTerminate();
		return -5;
	}
	// delete shader (once we've link them into the program, we no longer need them anymore)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set vertices
	float singleVertices[] = {
		-0.75f, 0.25f, 0.00f,
		-0.25f, 0.25f, 0.00f,
		-0.50f, 0.75f, 0.00f
	};

	// generate one vertex array obj
	unsigned int singleVAO;
	glGenVertexArrays(1, &singleVAO);
	glBindVertexArray(singleVAO);

	// generate one buffer id
	unsigned int singleVBO;
	glGenBuffers(1, &singleVBO);
	// bind buffer id by type (vertex buffer object type is GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, singleVBO);
	// copy vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(singleVertices), singleVertices, GL_STATIC_DRAW);
	// tell opengl how it should interpret the vertex data (vao how to read data from vbo)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//  note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	float doubleVertices[] = {
		 0.10f, 0.25f, 0.00f,
		 0.50f, 0.25f, 0.00f,
		 0.30f, 0.75f, 0.00f,
		 0.50f, 0.25f, 0.00f,
		 0.90f, 0.25f, 0.00f,
		 0.70f, 0.75f, 0.00f
	};

	unsigned int doubleVAO;
	glGenVertexArrays(1, &doubleVAO);
	glBindVertexArray(doubleVAO);

	unsigned int doubleVBO;
	glGenBuffers(1, &doubleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, doubleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(doubleVertices), doubleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float rectangleVertices[] = {
		-0.9f, -0.9f, 0.0f,
		-0.9f, -0.1f, 0.0f,
		-0.1f, -0.9f, 0.0f,
		-0.1f, -0.1f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2,		// first triangle
		1, 2, 3			// second triangle
	};

	unsigned int rectangleVAO;
	glGenVertexArrays(1, &rectangleVAO);
	glBindVertexArray(rectangleVAO);

	unsigned int rectangleVBO;
	glGenBuffers(1, &rectangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float rectangleLineVertices[] = {
		0.9f, -0.9f, 0.0f,
		0.9f, -0.1f, 0.0f,
		0.1f, -0.9f, 0.0f,
		0.1f, -0.1f, 0.0f
	};
	unsigned int rectangleLineindices[] = {
		0, 1, 2,		// first triangle
		1, 2, 3			// second triangle
	};

	unsigned int rectangleLineVAO;
	glGenVertexArrays(1, &rectangleLineVAO);
	glBindVertexArray(rectangleLineVAO);

	unsigned int rectangleLineVBO;
	glGenBuffers(1, &rectangleLineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleLineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleLineVertices), rectangleLineVertices, GL_STATIC_DRAW);

	unsigned int lineEBO;
	glGenBuffers(1, &lineEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleLineindices), rectangleLineindices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the program
		glUseProgram(shaderProgram);

		// bind vertex array
		glBindVertexArray(singleVAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(doubleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(rectangleVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// set mode is wireframe GL_LINE
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(rectangleLineVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// set mode is GL_FILL
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

