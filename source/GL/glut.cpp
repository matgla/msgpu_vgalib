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
#include <sys/time.h>
#include <sys/ioctl.h>

#include "messages/header.hpp"

#include "messages/ack.hpp"
#include "messages/change_mode.hpp"
#include "messages/draw_line.hpp"
#include "messages/set_pixel.hpp"
#include "messages/clear_screen.hpp"
#include "messages/swap_buffer.hpp"

#include "io.hpp"

static void (*display_callback)(void);

int wr_id;
int rd_id;

void glutInit(int *argcp, char **argv)
{
    wr_id = open("/tmp/gpu_com", O_WRONLY);
    rd_id = open("/tmp/gpu_com_2", O_RDONLY);
}

void glutSwapBuffers()
{
    static std::chrono::time_point<std::chrono::high_resolution_clock> prev;
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - prev);
    prev = now;
    if (elapsed.count() > 18000 || elapsed.count() < 16000)
    {
        std::cout << "Swap buffer offset detected: " << elapsed.count() << std::endl;
    }
    SwapBuffer msg; 
    write_msg(wr_id, msg);

    Ack ack;
    if (!read_msg(rd_id, ack))
    {
        printf("ACK FAILURE!!!!!!!!\n");
    }

    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now);
    std::cout << "Waited for ack: " << elapsed.count() << std::endl;
    
}

void glutInitDisplayMode(uint32_t mode)
{
    // TODO: implement
   // ChangeMode msg {.mode = 12 };
   // write_msg(wr_id, msg);
}

void glutCreateWindow(const char* name)
{
}

void glutDisplayFunc(void (*func)(void))
{
    display_callback = func;
}

uint64_t get_us()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec*static_cast<uint64_t>(1000000) + tv.tv_usec;
}

void glutMainLoop(void)
{
    while (true) 
    {
        static uint64_t prev = 0;
       
        display_callback();

        uint64_t now = get_us();
        uint64_t elapsed = now - prev;
        prev = now;
        std::cout << "Elapsed: " << elapsed << std::endl;

        if (elapsed < 16667)
        {
            std::cout << "Waiting for: " << std::chrono::microseconds(16667 - elapsed).count() << std::endl;
            uint64_t s = get_us();
            std::this_thread::sleep_for(std::chrono::microseconds(16667 - elapsed));
            std::cout << "Slept: " << (get_us() - s) << std::endl;
        }

    }
}

