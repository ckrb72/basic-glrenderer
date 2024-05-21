#version 410 core

in vec3 f_color;
in vec2 f_tex;

out vec4 final_color;

void main()
{
    final_color = vec4(f_color, 1.0);
}