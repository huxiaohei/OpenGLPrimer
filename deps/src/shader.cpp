/*****************************************************************
* Description
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 Αυ»Ά
****************************************************************/

#include <Shader/shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <GLAD/glad.h>


Shader::Shader(const char* vertexPath, const char* fragmentPath)
	:infoLog("/0") {
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FAIL_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

int Shader::compile() {
	unsigned int vertex, fragment;
	int success = 0;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vShaderCode = vertexCode.c_str();
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "COMPILE VERTEX SHADER ERROR:" << infoLog << std::endl;
		deleteShader(vertex);
		return success;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fShaderCode = fragmentCode.c_str();
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "COMPILE FRAGMENT SHADER ERROR:" << infoLog << std::endl;
		deleteShader(vertex);
		deleteShader(fragment);
		return success;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "LINK PROGRAM ERROR:" << infoLog << std::endl;
		deleteShader(vertex);
		deleteShader(fragment);
		return success;
	}
	deleteShader(vertex);
	deleteShader(fragment);
	return success;
}

char* Shader::getInfoLog() {
	return infoLog;
}

void Shader::setUniform(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::deleteShader(unsigned int shader) {
	glDeleteShader(shader);
}

void Shader::useProgram() {
	glUseProgram(program);
}
