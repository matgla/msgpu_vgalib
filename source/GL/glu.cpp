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

#include "GL/glu.h"

#include "io.hpp"
#include "messages/set_perspective.hpp"

void gluLookAt(GLdouble eyeX, 
    GLdouble eyeY,
    GLdouble eyeZ,
    GLdouble centerX, 
    GLdouble centerY,
    GLdouble centerZ,
    GLdouble upX,
    GLdouble upY,
    GLdouble upZ
)
{
}

void gluPerspective(GLdouble fovy,
    GLdouble aspect,
    GLdouble zNear,
    GLdouble zFar
)
{
    SetPerspective msg {
        .view_angle = static_cast<float>(fovy),
        .aspect = static_cast<float>(aspect),
        .z_near = static_cast<float>(zNear),
        .z_far = static_cast<float>(zFar)
    };

    write_msg(wr_id, msg);
}



