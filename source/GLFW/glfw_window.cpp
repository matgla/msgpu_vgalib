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

#include "messages/swap_buffer.hpp"

int io_id;

int glfwInit(void)
{
    const char* port = std::getenv("PORT");
    std::cout << "Opening serial port: " << port << std::endl;

    io_id = open(port, O_RDWR | O_NOCTTY | O_SYNC);

    termios tty;
    
    if (tcgetattr(io_id, &tty) != 0)
    {
        std::cout << "tcgetattr() failed for serial port" << std::endl;
        return GLFW_FALSE;
    }

    cfsetispeed(&tty, B230400);
    cfsetospeed(&tty, B230400);
    tty.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    tty.c_oflag &= ~(ONLCR | OCRNL);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    

    if (tcsetattr(io_id, TCSANOW, &tty) != 0)
    {
        std::cout << "tcsetaddr() failed" << std::endl;
        return GLFW_FALSE;
    }

    return GLFW_TRUE;
}

void glfwTerminate(void)
{
    close(io_id);
}

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{

}

void glfwMakeContextCurrent(GLFWwindow* window)
{
}

void glfwSwapBuffers(GLFWwindow* window)
{
    SwapBuffer msg;
    write_msg(io_id, msg);
}

void glfwPollEvents(void)
{
}

int glfwWindowShouldClose(GLFWwindow* window)
{
}




