// This file is part of msgpu project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cstdio>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <GL/gl.h>

GLuint vertexbuffer;

GLFWwindow* window;

const char* vertex_shader = 
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

const char* fragment_shader = 
"#version 400\n"
"out vec4 frag_color;"
"void main() {"
"  frag_color = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

static const GLfloat colors[] = {0.9, 0.9, 0.0, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
};

int main(int argc, char* argv[])
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

    float points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
       -0.5f, -0.5f,  0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    glVertexPointer(1, GL_FLOAT, 0, );

    GLuint colors_vbo = 1;
    glGenBuffers(1, &colors_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glColorPointer(1, GL_FLOAT, 0, 0);

//    GLuint vao = 0;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    do 
    {
        glClear(GL_COLOR_BUFFER_BIT);
     //   glUseProgram(shader_program);
      //  glBindVertexArray(vao);
        

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}
