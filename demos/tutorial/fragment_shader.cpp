/*
 *   Copyright (c) 2021 Mateusz Stadnik
 *   All rights reserved.
 */

vec4 &frag_color = *reinterpret_cast<vec4 *>(*out_argument[0]);

int main()
{
    frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}