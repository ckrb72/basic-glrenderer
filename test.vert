#version 410 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 vert_color;

void main()
{
    gl_Position = projection * vec4(a_pos, 1.0);

    vert_color = vec4(a_color, 1.0);
}