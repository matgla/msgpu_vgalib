// This file is part of msgpu_libgl project.
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

#include "GL/glut.h"

#include <chrono>
#include <thread>

#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h> 
#include <sys/ioctl.h>

#include "messages/header.hpp"

#include "messages/change_mode.hpp"
#include "messages/draw_line.hpp"
#include "messages/set_pixel.hpp"
#include "messages/clear_screen.hpp"
#include "messages/swap_buffer.hpp"

#include "io.hpp"

static void (*display_callback)(void);

int io_id;

void glutInit(int *argcp, char **argv)
{
    std::cout << "Opening serial port: " << argv[1] << std::endl;
    io_id = open(argv[1], O_RDWR | O_NOCTTY | O_SYNC);

    termios tty;
    
    if (tcgetattr(io_id, &tty) != 0)
    {
        std::cout << "tcgetattr() failed for serial port" << std::endl;
    }

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    tty.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    tty.c_oflag &= ~(ONLCR | OCRNL);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    

    if (tcsetattr(io_id, TCSANOW, &tty) != 0)
    {
        std::cout << "tcsetaddr() failed" << std::endl;
    }
}

void glutSwapBuffers()
{
    SwapBuffer b;
    write_msg(b);
}

void glutInitDisplayMode(uint32_t mode)
{
    // TODO: implement
    ChangeMode msg {.mode = 12 };
    write_msg(msg);
}

void glutCreateWindow(char* name)
{
}

void glutDisplayFunc(void (*func)(void))
{
    display_callback = func;
}

void glutMainLoop(void)
{
    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        display_callback();
    }
}


