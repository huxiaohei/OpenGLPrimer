/*****************************************************************
* Description ´°¿Ú
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 Áõ»¢
****************************************************************/

#include <GLFW/glfw3.h>

class Window {
public:
	Window(const char* title, int width, int heigh);
	~Window();
	void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
	void makeContextCurrent();
	void setShouldClose(bool close);
	bool shouldClose();
	void swapBuffers();
	static float getTime();
	static void pollEvents();
	GLFWwindow* getWindow() { return window; };
private:
	GLFWwindow* window = NULL;

};




