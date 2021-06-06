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

#include <stdint.h>
#include <cstddef>

#ifdef __cplusplus
extern "C"
{
#endif

extern int io_id;

typedef float GLfloat;
typedef double GLdouble;
typedef int GLint;
typedef unsigned int GLuint;

typedef uint32_t GLenum;
typedef uint32_t GLbitfield;
typedef int GLsizei;
typedef uint32_t GLsizeiptr;
typedef bool GLboolean;
typedef char GLchar;

#define GL_TRUE 1
#define GL_FALSE 0

#define GL_QUADS 1 
#define GL_TRIANGLES 2 

#define GL_COLOR_BUFFER_BIT (1 << 1)
#define GL_DEPTH_BUFFER_BIT (1 << 2)

#define GL_LIGHT0 0 
#define GL_DIFFUSE 0 
#define GL_POSITION 0 
#define GL_LIGHTING 0 
#define GL_DEPTH_TEST 0 
#define GL_PROJECTION 0 
#define GL_MODELVIEW 0 

#define GL_VERTEX_ARRAY 0
#define GL_COLOR_ARRAY 1

#define GL_FLOAT 1 

void glEnableClientState(GLenum attrib);

void glGenVertexArrays(GLsizei n, GLuint *arrays);

void glGenBuffers(GLsizei n, GLuint *buffers);

#define GL_ARRAY_BUFFER 1
void glBindBuffer(GLenum target, GLuint buffer);

void glBindVertexArray(GLuint array);

#define GL_STATIC_DRAW  1  
#define GL_DYNAMIC_DRAW 2
void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

void glEnableVertexAttribArray(GLuint index);

#define GL_VERTEX_SHADER 1 
#define GL_FRAGMENT_SHADER 2
GLuint glCreateShader(GLenum shaderType);
void glCompileShader(GLuint shader);
GLuint glCreateProgram(void);
void glAttachShader(GLuint program, 
    GLuint shader);
void glLinkProgram(GLuint program);
void glUseProgram(GLuint program);
void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);

void glDrawArrays(GLenum mode, GLint first, GLsizei count);

void glBegin(GLenum mode);
void glEnd();

void glNormal3fv(const GLfloat* v);
void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
void glVertex3fv(const GLfloat* v);

// Clear API 

void glClear(GLbitfield mask);
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void glEnable(GLenum cap);
void glLightfv(GLenum light, GLenum pname, const GLfloat* params);
void glMatrixMode(GLenum mode);
void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#ifdef __cplusplus
}
#endif


