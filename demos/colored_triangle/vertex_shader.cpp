/*
 *   Copyright (c) 2021 Mateusz Stadnik
 *   All rights reserved.

 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:

 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.

 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 */
#include <cstdio>
#define layout(arg) extern __attribute__((alias(argument_##arg)))

// vec3 &aPos        = *reinterpret_cast<vec3 *>(*in_argument[0]);

int main()
{
    vec3 &aPos        = *reinterpret_cast<vec3 *>(*in_argument[0]);
    vec3 &vertexColor = *reinterpret_cast<vec3 *>(*in_argument[1]);
    const mat4 &MVP   = *reinterpret_cast<mat4 *>(*in_argument[2]);

    printf("Fragment color: {%f %f %f}\n", vertexColor[0], vertexColor[1], vertexColor[2]);
    vec3 &fragmentColor = *reinterpret_cast<vec3 *>(*out_argument[0]);
    static_cast<void>(MVP);
    gl_Position   = vec4(aPos, 1.0);
    fragmentColor = vertexColor;
}