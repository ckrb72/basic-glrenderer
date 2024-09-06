#version 410 core

in vec3 f_normal;
in vec3 f_tex;
in vec4 f_color;

out vec4 final_color;

void main()
{
    final_color = f_color;
}