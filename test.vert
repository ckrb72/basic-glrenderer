#version 410 core
layout(location = 0) in vec3 a_pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 vert_color;

void main()
{
    gl_Position = projection * vec4(a_pos, 1.0);
}