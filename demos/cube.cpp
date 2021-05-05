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
#include <GL/glut.h> 

#include <GL/gl.h>

struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Triangle 
{
    Vertex v[3];
};

struct Mesh 
{
    Triangle triangles[12]; 
};

const Mesh mesh {
    .triangles = {
        {{ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f} }},
        {{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f} }},
        {{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f} }},
        {{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f} }},
        {{ {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f} }},
        {{ {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} }},
        {{ {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} }},
        {{ {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f} }},
        {{ {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} }},
        {{ {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f} }},
        {{ {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} }},
        {{ {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} }},
    }
};
void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                glVertex3f(mesh.triangles[i].v[j].x, mesh.triangles[i].v[j].y, mesh.triangles[i].v[j].z);
            }
        }
    glEnd();

    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0, 1.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    
    gluLookAt(0.0, 0.0, 5.0,
        0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0
    );

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("3D cube");

    glutDisplayFunc(render);

    init();

    glutMainLoop();
}


