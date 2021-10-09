// https://github.com/opengl-tutorials/ogl/blob/master/tutorial04_colored_cube/ColorFragmentShader.fragmentshader

#version 330 core

in vec3 fragmentColor;
out vec4 color;

void main()
{
    color = vec4(fragmentColor, 1.0f);
}