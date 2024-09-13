#version 410 core

in vec2 text_coord;
out vec4 color;

uniform sampler2D container;
uniform vec3 tex_color;

void main()
{
    color = texture(container, text_coord) * vec4(tex_color, 1.0);
}