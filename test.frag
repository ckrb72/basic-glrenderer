#version 410 core

in vec2 text_coord;
in vec4 vert_color;
out vec4 color;

uniform sampler2D container;

void main()
{
    color = texture(container, text_coord);
}