/*
 *   Copyright (c) 2021 Mateusz Stadnik
 *   All rights reserved.
 */

#include "load_shaders.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string load_file(const char *file)
{
    std::string shader_code;
    std::ifstream vs(file, std::ios::in | std::ios::ate);
    if (vs.is_open())
    {
        const std::size_t filesize = vs.tellg();
        vs.seekg(0, vs.beg);
        shader_code.reserve(filesize);
        vs.read(&shader_code[0], filesize);
        vs.close();
    }
    else
    {
        printf("Can't open file: %s\n", file);
        std::abort();
    }
    return shader_code;
}

GLuint load_shaders(const char *v_path, const char *f_path)
{
    GLuint vertex_shader_id   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

#ifdef COMPILED_SHADER
    const char *vertex_code   = v_path;
    const char *fragment_code = f_path;
#else
    const std::string vc      = load_file(v_path);
    const std::string fc      = load_file(f_path);
    const char *vertex_code   = vc.c_str();
    const char *fragment_code = fc.c_str();
#endif
    GLint result = GL_FALSE;
    int info_log_length;

    glShaderSource(vertex_shader_id, 1, &vertex_code, nullptr);
    glCompileShader(vertex_shader_id);
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0)
    {
        std::vector<char> vertex_shader_error(info_log_length + 1);
        glGetShaderInfoLog(vertex_shader_id, info_log_length, nullptr, vertex_shader_error.data());
        printf("%s\n", vertex_shader_error.data());
    }
    glShaderSource(fragment_shader_id, 1, &fragment_code, nullptr);
    glCompileShader(fragment_shader_id);
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0)
    {
        std::vector<char> fragment_shader_error(info_log_length + 1);
        glGetShaderInfoLog(fragment_shader_id, info_log_length, nullptr,
                           fragment_shader_error.data());
        printf("%s\n", fragment_shader_error.data());
    }

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0)
    {
        std::vector<char> program_error(info_log_length + 1);
        glGetShaderInfoLog(program_id, info_log_length, nullptr, program_error.data());
        printf("%s\n", program_error.data());
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
