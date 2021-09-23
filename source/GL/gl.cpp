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
#include "messages/bind.hpp"
#include "messages/buffer_target_type.hpp"
#include "messages/clear_screen.hpp"
#include "messages/draw_arrays.hpp"
#include "messages/end_primitives.hpp"
#include "messages/generate_names.hpp"
#include "messages/write_buffer_data.hpp"
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

uint8_t clear_color = 0;
void glClear(GLbitfield mask)
{
    ClearScreen msg{
        .color = clear_color,
    };
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
    return static_cast<uint8_t>(r * 8) << 5 | static_cast<uint8_t>(g * 8) << 2 |
           static_cast<uint8_t>(b * 4);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    clear_color = to_rgb332(red, green, blue);
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

BufferTargetType convert_buffer_target_type(GLenum target)
{
    switch (target)
    {
    case GL_ARRAY_BUFFER:
        return BufferTargetType::ArrayBuffer;
    default:
        return static_cast<BufferTargetType>(0);
    };
};

void glBindBuffer(GLenum target, GLuint buffer)
{
    BindObject msg;

    msg.target    = convert_buffer_target_type(target);
    msg.object_id = buffer;
    msg.type      = BindObjectType::BindBuffer;
    write_msg(wr_id, msg);
}

void glBindVertexArray(GLuint array)
{
    BindObject msg;

    msg.type      = BindObjectType::BindVertexArray;
    msg.object_id = array;
}

void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
    const std::size_t parts = size / sizeof(WriteBufferData::data);
    const std::size_t rest  = size % sizeof(WriteBufferData::data);

    uint16_t index                   = 0;
    const PrepareForData prepare_msg = {
        .named     = 0,
        .target    = convert_buffer_target_type(target),
        .usage     = usage,
        .object_id = 0,
        .size      = size,
    };
    write_msg(wr_id, prepare_msg);

    WriteBufferData msg;
    msg.size = rest;
    msg.part = index;
    std::memcpy(msg.data, data, rest);

    write_msg(wr_id, msg);
    ++index;
    for (std::size_t i = 0; i < parts; ++i)
    {
        std::memcpy(msg.data,
                    static_cast<const uint8_t *>(data) + rest + i * sizeof(WriteBufferData::data),
                    sizeof(WriteBufferData::data));
        msg.part = index++;
        msg.size = sizeof(WriteBufferData::data);
        write_msg(wr_id, msg, sizeof(WriteBufferData));
    }
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
    DrawArrays msg{
        .mode  = static_cast<uint8_t>(mode),
        .first = static_cast<uint16_t>(first),
        .count = static_cast<uint16_t>(count),
    };

    write_msg(wr_id, msg);
}

