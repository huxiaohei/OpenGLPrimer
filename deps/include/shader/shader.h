/*****************************************************************
* Description
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 Αυ»Ά
****************************************************************/

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {

public:
	Shader(const char* vertexPath, const char* fragmnet);

	int compile();
	void useProgram();
	char* getInfoLog();
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, glm::mat4 value) const;
	static unsigned int loadTexture(const char* path);
private:
	std::string vertexCode;
	std::string fragmentCode;
	unsigned int program = 0;
	char infoLog[512];

	void deleteShader(unsigned int shader);
};

