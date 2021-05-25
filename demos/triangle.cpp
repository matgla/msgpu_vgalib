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

/* This is example file for test purposes */

#include <thread>

#include <GL/gl.h> 
#include <GL/glut.h> 

#include "messages/draw_triangle.hpp" 

#include "io.hpp"

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutCreateWindow("2D triangle");
    //glutDisplayFunc(render);

    glClear(GL_COLOR_BUFFER_BIT);
    DrawTriangle t = {
        .fill = FillType::Solid,
        .color = 8,
        .x1 = 100,
        .y1 = 60,
        .x2 = 240, 
        .y2 = 60, 
        .x3 = 160,
        .y3 = 200 
    };

    write_msg(t);
//    t = { 
//        .fill = FillType::Solid,
//        .color = 3, 
//        .x1 = 160, 
//        .y1 = 60, 
//        .x2 = 240, 
//        .y2 = 200, 
//        .x3 = 240,
//        .y3 = 60
//    };
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
 
    write_msg(t);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    glutSwapBuffers();
    //glutMainLoop();
}
