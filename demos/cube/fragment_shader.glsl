// https://github.com/opengl-tutorials/ogl/blob/master/tutorial04_colored_cube/ColorFragmentShader.fragmentshader

#version 400 

in vec3 fragmentColor;
out vec3 color;

void main() 
{
    color = fragmentColor;
}