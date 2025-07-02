#include "shaders.h"
#include "../core/seethe.h"
#include "../core/file.h"

GLuint create_shader_program(const char* vertex_path, const char* fragment_path)
{
    GLuint vertex_shader = compile_shader_from_path(GL_VERTEX_SHADER, vertex_path);
    if (vertex_shader == 0) return 0;

    GLuint fragment_shader = compile_shader_from_path(GL_FRAGMENT_SHADER, fragment_path);
    if (fragment_shader == 0) 
    {
        glDeleteShader(vertex_shader);
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program == 0) 
    {
        log_error("Failed to create shader program");
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Check linking status
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) 
    {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        log_error("program linking failed:\n%s", infoLog);
        glDeleteProgram(program);
        program = 0;
    }

    // Clean up shaders (they're now in the program)
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

GLuint compile_shader(const GLenum type, const char* source) 
{
    GLuint shader_id = glCreateShader(type);
    if (shader_id == 0) 
    {
        log_error("failed to create shader");
        return 0;
    }

    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);  // Fixed typo here

    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        char infoLog[512];
        glGetShaderInfoLog(shader_id, sizeof(infoLog), NULL, infoLog);
        log_error("shader compilation failed:\n%s", infoLog);
        glDeleteShader(shader_id);
        return 0;
    }

    return shader_id;
}

GLuint compile_shader_from_path(const GLenum type, const char* local_file_path)
{
	char* shader_source = file_read_local(local_file_path);
	GLuint shader_id = compile_shader(type, shader_source);
	free(shader_source);

	return shader_id;
}
