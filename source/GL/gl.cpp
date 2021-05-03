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

#include "GL/gl.h"

#include "io.hpp"

#include "messages/clear_screen.hpp"

#include "messages/begin_primitives.hpp"
#include "messages/end_primitives.hpp"
#include "messages/write_vertex.hpp"

#include "io.hpp"

void glInit(GLenum mode) 
{

}

uint8_t convert_mode(GLenum mode)
{
    switch (mode)
    {
        case GL_TRIANGLES: return PrimitiveType::triangle;
        case GL_QUADS: return PrimitiveType::square; 
    }
    return PrimitiveType::none;
}

void glBegin(GLenum mode)
{
    BeginPrimitives msg { .type = convert_mode(mode) };
    write_msg(msg);
}

void glEnd() 
{
    EndPrimitives msg; 
    write_msg(msg);
}

void glNormal3fv(const GLfloat* v)
{

}

void glVertex3fv(const GLfloat* v)
{
    WriteVertex msg {
        .x = v[0],
        .y = v[1],
        .z = v[2]
    };

    write_msg(msg);
}

void glClear(GLbitfield mask)
{
    ClearScreen msg;
    write_msg(msg);
}

void glEnable(GLenum cap)
{
}
void glLightfv(GLenum light, GLenum pname, const GLfloat* params)
{
}
void glMatrixMode(GLenum mode)
{
}
void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
}


