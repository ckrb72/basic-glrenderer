#pragma once
#include <stdint.h>
#include <string>

class Shader
{

private:
    uint32_t id;

    bool compile_shader(const std::string& vertex_source, const std::string& fragment_source);

public:

    Shader() {};

    ~Shader();

    bool create(const std::string& vertex_path, const std::string& fragment_path);

};