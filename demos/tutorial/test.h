#pragma once 

struct vec3 
{
    float x;
    float y;
    float z;
};

struct vec4
{
    vec4(const vec3& v, float w)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(w)
    {
    }

    float x;
    float y;
    float z;
    float w;
};

extern vec4 gl_Position;