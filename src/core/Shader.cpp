#include "Shader.h"
#include <graphics.h>
#include <iostream>
#include <fstream>

#define MAX_LOG 512

Shader::~Shader()
{
    glDeleteProgram(m_id);
}


bool Shader::load(const std::string& vertex_path, const std::string& fragment_path)
{

    std::string source_line;    


    //Load vertex string
    std::ifstream input;
    input.open(vertex_path);

    if(!input.is_open())
        return false;

    std::string vertex_source;

    while(std::getline(input, source_line))
    {
        vertex_source += source_line + "\n";
    }

    input.close();


    //Load fragment string
    input.open(fragment_path);

    if(!input.is_open())
        return false;

    std::string fragment_source;

    while(std::getline(input, source_line))
    {
        fragment_source += source_line + "\n";
    }

    //compile shader
    return compile_shader(vertex_source, fragment_source);
}


bool Shader::compile_shader(const std::string& vertex_source, const std::string& fragment_source)
{

    #ifdef DEBUG
    int success;
    char log[MAX_LOG];
    #endif

    const char* vert_source = vertex_source.c_str();

    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char* const*)&vert_source, NULL);
    glCompileShader(vertex_shader);

    #ifdef DEBUG
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, MAX_LOG, nullptr, log);
        std::cerr << log << std::endl;
        glDeleteShader(vertex_shader);
        return false;
    }
    #endif

    const char* frag_source = fragment_source.c_str();

    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char* const*)&frag_source, NULL);
    glCompileShader(fragment_shader);


    #ifdef DEBUG
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, MAX_LOG, nullptr, log);
        std::cerr << log << std::endl;
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return false;
    }
    #endif

    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    #ifdef DEBUG
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, MAX_LOG, nullptr, log);
        std::cerr << log << std::endl;
        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);
        return false;
    }
    #endif

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    m_id = program;

    return true;
}

void Shader::bind()
{
    glUseProgram(m_id);
}

void Shader::unbind()
{
    glUseProgram(0);
}


//Can optimize the hell out of all these functions by saving uniform locations in a map or something.
//Will implement this later
void Shader::set_mat4fv(const std::string& name, float* matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::set_vec3f(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::set_vec3fv(const std::string& name, float* vec)
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, vec);
}

void Shader::set_int(const std::string& name, int i)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), i);
}
