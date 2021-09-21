// This file is part of msgpu_vgalib project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "GL/gl.h"

#include <algorithm>

#include "io.hpp"
#include "messages/ack.hpp"
#include "messages/begin_primitives.hpp"
#include "messages/clear_screen.hpp"
#include "messages/end_primitives.hpp"
#include "messages/generate_names.hpp"
#include "messages/write_vertex.hpp"

void glInit(GLenum mode)
{
}

uint8_t convert_mode(GLenum mode)
{
    switch (mode)
    {
    case GL_TRIANGLES:
        return PrimitiveType::triangle;
    case GL_QUADS:
        return PrimitiveType::square;
    }
    return PrimitiveType::none;
}

void glBegin(GLenum mode)
{
    BeginPrimitives msg{.type = convert_mode(mode)};
    write_msg(wr_id, msg);
}

void glEnd()
{
    EndPrimitives msg;
    write_msg(wr_id, msg);
}

void glNormal3fv(const GLfloat *v)
{
}

void glVertex3fv(const GLfloat *v)
{
    WriteVertex msg{.x = v[0], .y = v[1], .z = v[2]};

    write_msg(wr_id, msg);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
    WriteVertex msg{.x = x, .y = y, .z = z};

    write_msg(wr_id, msg);
}

void glClear(GLbitfield mask)
{
    ClearScreen msg;
    write_msg(wr_id, msg);
}

void glEnable(GLenum cap)
{
}
void glLightfv(GLenum light, GLenum pname, const GLfloat *params)
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

constexpr uint8_t to_rgb332(float r, float g, float b)
{
    return static_cast<uint8_t>(r * 7) << 5 | static_cast<uint8_t>(g * 7) << 2 |
           static_cast<uint8_t>(b * 3);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
}

void glEnableClientState(GLenum attrib)
{
}

void __generateNames(GLsizei n, GLuint *arrays, ObjectType type)
{
    uint32_t loops = n / sizeof(GenerateNamesResponse::data);

    uint8_t elements =
        std::min(static_cast<std::size_t>(n), n % sizeof(GenerateNamesResponse::data));
    std::size_t index = 0;
    if (elements)
    {
        GenerateNamesRequest req{
            .elements = elements,
            .type     = type,
        };
        write_msg(wr_id, req);

        GenerateNamesResponse resp;
        printf("Wait for ids\n");
        read_msg(rd_id, resp);

        if (resp.error_code != 0)
        {
            printf("Received error code for GenerateNames: %d\n", resp.error_code);
            std::abort();
        }

        for (; index < elements; ++index)
        {
            arrays[index] = resp.data[index];
        }
    }
    for (uint32_t i = 0; i < loops; ++i)
    {
        uint8_t elements = 30;
        GenerateNamesRequest req{
            .elements = sizeof(GenerateNamesResponse::data),
            .type     = type,
        };
        write_msg(wr_id, req);

        GenerateNamesResponse resp;
        read_msg(rd_id, resp);

        if (resp.error_code != 0)
        {
            printf("Received error code for GenerateNames: %d\n", resp.error_code);
            std::abort();
        }

        for (int i = 0; i < sizeof(GenerateNamesResponse::data); ++i)
        {
            arrays[index] = resp.data[i];
            ++index;
        }
    }

    printf("Received ids: {");
    for (int i = 0; i < n; ++i)
    {
        printf("%d,", arrays[i]);
    }
    printf("\n");
}

void glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    __generateNames(n, arrays, ObjectType::VertexArray);
}

void glGenBuffers(GLsizei n, GLuint *buffers)
{
    __generateNames(n, buffers, ObjectType::Buffer);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
}

void glBindVertexArray(GLuint array)
{
}

void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                           GLsizei stride, const void *pointer)
{
}

void glEnableVertexAttribArray(GLuint index)
{
}

GLuint glCreateShader(GLenum shaderType)
{
}

void glCompileShader(GLuint shader)
{
}

GLuint glCreateProgram(void)
{
}

void glAttachShader(GLuint program, GLuint shader)
{
}

void glLinkProgram(GLuint program)
{
}

void glUseProgram(GLuint program)
{
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
{
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
}

