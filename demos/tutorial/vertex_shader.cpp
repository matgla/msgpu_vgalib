
void* argument_0;

#define layout(arg) extern __attribute__((alias(argument_##arg)))

extern vec3 aPos __attribute__((alias("argument_0")));

int main()
{
    gl_Position = vec4(aPos, 1.0);
}