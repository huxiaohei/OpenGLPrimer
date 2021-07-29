/*****************************************************************
* Description
* Email huxiaoheigame@gmail.com
* Created on
* Copyright (c) 2021 刘虎
****************************************************************/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Window/window.h>
#include <Shader/shader.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGH 720

void framebufferSizeCallback(GLFWwindow* window, int width, int heigh) {
    glViewport(0, 0, width, heigh);
    std::cout << "width:" << width << " heigh:" << heigh << std::endl;
}

int main() {

    Window* window = new Window("Transform", WINDOW_WIDTH, WINDOW_HEIGH);
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
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGH);
    Shader* shader = new Shader("./vshader.glsl", "./fshader.glsl");
    int success = shader->compile();
    if (!success) {
        std::cout << "COMPILE SHADER ERROR: " << shader->getInfoLog() << std::endl;
        delete window;
        return -2;
    }

    float vPoint[] = {
        -0.5,  0.5, 0.0, 0.0, 1.0,
        -0.5, -0.5, 0.0, 0.0, 0.0,
         0.5, -0.5, 0.0, 1.0, 0.0,
         0.5,  0.5, 0.0, 1.0, 1.0
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vPoint), vPoint, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int texture = Shader::loadTexture("../res/img/awesomeface.png");

    while (!window->shouldClose()) {
        glClearColor(0.0, 0.0, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = Window::getTime();
        shader->setUniform("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        shader->useProgram();

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5, 0.5, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 1.0));
        trans = glm::rotate(trans, glm::radians(30.0f * time), glm::vec3(0.0, 0.0, 1.0));
        shader->setUniform("transform", trans);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5, 0.5, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5 * abs(sin(time)), 0.5 * abs(sin(time)), 1.0));
        shader->setUniform("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5, -0.5, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 1.0));
        trans = glm::translate(trans, glm::vec3(0.5 * sin(3.0*time), 0.0, 0.0));
        shader->setUniform("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 1.0));
        trans = glm::rotate(trans, glm::radians(30.0f * time), glm::vec3(0.0, 1.0, 0.0));
        shader->setUniform("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window->swapBuffers();
        Window::pollEvents();
    }
    delete window;
    delete shader;
    return 0;
}

