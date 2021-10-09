/*
 *   Copyright (c) 2021 Mateusz Stadnik
 *   All rights reserved.
 */
// Example from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#include <cstdio>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "load_shaders.hpp"

GLFWwindow *window;

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(320, 240, "Triangle Demo", nullptr, nullptr);
    if (window == NULL)
    {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

    GLuint pid = load_shaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f, 0.5f, 0.0f, 0.0f,  0.0f,  1.0f,
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(pid);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // for now I don't know how to set framelimit
        std::this_thread::sleep_for(std::chrono::milliseconds(31));
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glDeleteBuffers(1, &vbo);
    glDeleteProgram(pid);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
}
