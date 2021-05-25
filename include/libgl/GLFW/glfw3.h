// This file is part of msgpu_vgalib project.
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

#pragma once 

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

// Globals 

#define GLFW_TRUE 1 
#define GLFW_FALSE 0

typedef struct {

} GLFWwindow;

typedef struct {

} GLFWmonitor;

// Window 
int glfwInit(void);
void glfwTerminate(void);

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);

void glfwMakeContextCurrent(GLFWwindow* window);

void glfwSwapBuffers(GLFWwindow* window);
void glfwPollEvents(void);

int glfwWindowShouldClose(GLFWwindow* window);

// IO 
#define GLFW_STICKY_KEYS    0x00033002 

#define GLFW_PRESS          1

#define GLFW_KEY_ESCAPE     256 


void glfwSetInputMode(GLFWwindow* window, int mode, int value);

int glfwGetKey(GLFWwindow* window, int key);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

