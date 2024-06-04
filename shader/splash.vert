#version 410 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 f_tex;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);

    f_tex = v_tex;
}