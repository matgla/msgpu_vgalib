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

#include <cstdlib>
#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h> 
#include <sys/ioctl.h>


#include "GLFW/glfw3.h" 

#include "io.hpp"

#include "messages/ack.hpp"
#include "messages/swap_buffer.hpp"

int wr_id;
int rd_id;

int glfwInit(void)
{
    wr_id = open("/tmp/gpu_com", O_WRONLY);
    rd_id = open("/tmp/gpu_com_2", O_RDONLY);
    return GLFW_TRUE;
}

void glfwTerminate(void)
{
    close(wr_id);
    close(rd_id);
}

static GLFWwindow window;

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    return &window;
}

void glfwMakeContextCurrent(GLFWwindow* window)
{
}

void glfwSwapBuffers(GLFWwindow* window)
{
    SwapBuffer msg;
    write_msg(wr_id, msg);

    Ack ack;
    if (!read_msg(rd_id, ack))
    {
        printf("ACK FAILURE!!!!!!!!\n");
    }
}

void glfwPollEvents(void)
{
}

int glfwWindowShouldClose(GLFWwindow* window)
{
    return 0;
}




