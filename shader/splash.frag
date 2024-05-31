#version 410 core

in vec2 f_tex;
out vec4 final_color;

uniform sampler2D sprite_sheet;

void main()
{
    final_color = texture(sprite_sheet, f_tex);
}