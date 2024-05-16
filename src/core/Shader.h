#pragma once
#include <stdint.h>
#include <string>

class Shader
{

private:
    uint32_t m_id;

    bool compile_shader(const std::string& vertex_source, const std::string& fragment_source);

public:

    Shader() {};

    ~Shader();

    bool load(const std::string& vertex_path, const std::string& fragment_path);

    void set_mat4fv(const std::string& name, float* matrix);

    void set_vec3f(const std::string& name, float a, float b, float c);

    //TODO:Change this declaration to use lnal
    void set_vec3fv(const std::string& name, float* vec);

    void set_int(const std::string& name, int i);

    void bind();

    void unbind();
};