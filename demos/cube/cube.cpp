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

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a
// triangle. A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3
// vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,
    1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,
    -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,
};
static const GLfloat g_color_buffer_data[] = {
    0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f, 0.822f, 0.569f, 0.201f,
    0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f, 0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f,
    0.359f, 0.583f, 0.152f, 0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f,
    0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f, 0.676f, 0.977f, 0.133f,
    0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f, 0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f,
    0.543f, 0.021f, 0.978f, 0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f,
    0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f, 0.722f, 0.645f, 0.174f,
    0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f, 0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f,
    0.393f, 0.621f, 0.362f, 0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f,
};

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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint pid      = load_shaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    GLuint matrixID = glGetUniformLocation(pid, "MVP");

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view       = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model      = glm::mat4(1.0f);
    glm::mat4 mvp        = projection * view * model;

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,
                 GL_STATIC_DRAW);
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(pid);
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // for now I don't know how to set framelimit
        std::this_thread::sleep_for(std::chrono::milliseconds(31));
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(pid);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
}
