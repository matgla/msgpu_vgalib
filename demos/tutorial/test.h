#pragma once

struct vec3
{
    float x;
    float y;
    float z;
};

struct vec4
{
    vec4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    vec4(const vec3 &v, float w)
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
extern void *argument_0;

extern void *out_argument_0;