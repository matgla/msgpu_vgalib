// Sanity check in script 
//#version 330 core 

// layout(location = 0) in vec3 vertexPosition_modelspace; 

struct vec4
{
    
};

vec4 gl_Position;

void main() 
{
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
}
