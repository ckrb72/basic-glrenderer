#version 410 core

in vec4 vert_color;
out vec4 color;

void main()
{
    color = vert_color;
}