// https://github.com/opengl-tutorials/ogl/blob/master/tutorial04_colored_cube/TransformVertexShader.vertexshader
#version 400

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
uniform mat4 MVP;

void main()
{
    gl_Position   = MVP * vec4(vertexPosition_modelspace, 1);
    fragmentColor = vertexColor;
}