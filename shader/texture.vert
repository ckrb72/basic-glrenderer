#version 410 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 text_coord;

void main()
{
    gl_Position = projection * view * vec4(a_pos, 1.0);
    text_coord = a_texCoord;
}