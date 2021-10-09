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
#include <cmath>
#include <fstream>

#include "io.hpp"
#include "messages/ack.hpp"
#include "messages/allocate_program.hpp"
#include "messages/attach_shader.hpp"
#include "messages/begin_primitives.hpp"
#include "messages/begin_program_write.hpp"
#include "messages/bind.hpp"
#include "messages/buffer_target_type.hpp"
#include "messages/clear_screen.hpp"
#include "messages/draw_arrays.hpp"
#include "messages/end_primitives.hpp"
#include "messages/generate_names.hpp"
#include "messages/program_write.hpp"
#include "messages/set_vertex_attrib.hpp"
#include "messages/use_program.hpp"
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

void glDepthFunc(GLenum func)
{
}

GLint glGetUniformLocation(GLuint program, const GLchar *name)
{
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
}

constexpr uint8_t to_rgb332(float r, float g, float b)
{
    return static_cast<uint8_t>(roundf(r * 7)) << 5 | static_cast<uint8_t>(roundf(g * 7)) << 2 |
           static_cast<uint8_t>(roundf(b * 3));
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

void glDeleteVertexArrays(GLsizei m, const GLuint *arrays)
{
}

void glGenBuffers(GLsizei n, GLuint *buffers)
{
    __generateNames(n, buffers, ObjectType::Buffer);
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
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
    SetVertexAttrib msg{.index      = index,
                        .size       = size,
                        .normalized = normalized,
                        .type       = type,
                        .stride     = stride,
                        .pointer    = reinterpret_cast<std::size_t>(pointer)};

    write_msg(wr_id, msg);
}

void glEnableVertexAttribArray(GLuint index)
{
}

void glDisableVertexAttribArray(GLuint index)
{
}

uint8_t convert_shader_type(GLenum shaderType)
{
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        return AllocateProgramType::AllocateVertexShader;
    case GL_FRAGMENT_SHADER:
        return AllocateProgramType::AllocateFragmentShader;
    }
    return 0;
}

GLuint glCreateShader(GLenum shaderType)
{
    AllocateProgramRequest req{
        .program_type = convert_shader_type(shaderType),
    };

    write_msg(wr_id, req);

    AllocateProgramResponse resp;
    read_msg(rd_id, resp);
    return resp.program_id;
}

void glCompileShader(GLuint shader)
{
}

GLuint glCreateProgram(void)
{
    AllocateProgramRequest req{
        .program_type = AllocateProgramType::AllocateProgram,
    };

    write_msg(wr_id, req);

    AllocateProgramResponse resp;

    read_msg(rd_id, resp);
    return resp.program_id;
}

void glDeleteProgram(GLuint program)
{
}

void glGetProgramiv(GLuint program, GLenum pname, GLint *params)
{
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
}

void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
{
}

void glAttachShader(GLuint program, GLuint shader)
{
    AttachShader req{
        .program_id = static_cast<uint8_t>(program),
        .shader_id  = static_cast<uint8_t>(shader),
    };

    write_msg(wr_id, req);
}

void glLinkProgram(GLuint program)
{
}

void glDetachShader(GLuint program, GLuint shader)
{
}

void glUseProgram(GLuint program)
{
    UseProgram req{.program_id = static_cast<uint8_t>(program)};

    write_msg(wr_id, req);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
{
    printf("Here come the crash again\n");
    const char *filename = *string;
    printf("Filename: %s\n", filename);
    std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);

    if (!file)
    {
        printf("Can't open file: %s\n", filename);
    }
    std::size_t file_size = file.tellg();

    printf("Sending begin program write with size: %d\n", file_size);
    BeginProgramWrite msg{
        .program_id = static_cast<uint8_t>(shader), // not able to deduce here
        .size       = file_size,
    };

    write_msg(wr_id, msg);

    uint8_t part = 0;
    file.seekg(0, file.beg);
    while (file_size > 0)
    {
        std::size_t size = std::min(file_size, sizeof(ProgramWrite::data));
        ProgramWrite p{
            .size = size,
            .part = part++,
        };
        file.read(reinterpret_cast<char *>(&p.data[0]), size);
        write_msg(wr_id, p);
        file_size -= size;
    }
}

void glDeleteShader(GLuint shader)
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
