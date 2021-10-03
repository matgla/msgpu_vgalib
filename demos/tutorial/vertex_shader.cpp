#define layout(arg) extern __attribute__((alias(argument_##arg)))

vec3 aPos = *reinterpret_cast<vec3 *>(argument_0);

#include <cstdio>

int main()
{
    printf("Vertex shader called\n");
    gl_Position = vec4(aPos, 1.0);
}