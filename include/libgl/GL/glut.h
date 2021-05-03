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

#pragma once 

#include "GL/gl.h"
#include "GL/glu.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define GLUT_DOUBLE 0 
#define GLUT_RGB 0 
#define GLUT_DEPTH 0 

void glutInit(int *argcp, char **argv);

void glutSwapBuffers();

void glutInitDisplayMode(uint32_t mode);
void glutCreateWindow(char* name);
void glutDisplayFunc(void (*func)(void));
void glutMainLoop(void);

#ifdef __cplusplus
}
#endif


