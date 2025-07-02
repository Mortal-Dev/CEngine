#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>

GLuint create_shader_program(const char* vertex_path, const char* fragment_path);

GLuint compile_shader(const GLenum type, const char* source);

GLuint compile_shader_from_path(const GLenum type, const char* file_path);

#endif