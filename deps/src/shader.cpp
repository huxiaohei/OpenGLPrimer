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
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

void Shader::setUniform(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


unsigned int Shader::loadTexture(const char* path) {
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

void Shader::deleteShader(unsigned int shader) {
	glDeleteShader(shader);
}

void Shader::useProgram() {
	glUseProgram(program);
}

