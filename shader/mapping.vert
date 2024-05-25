#version 410 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_pos;
out vec3 f_normal;
out vec2 f_tex;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);

    //Get the position of the fragment in world space
    frag_pos = vec3(model * vec4(v_pos, 1.0));

    //Very costly (would want to do this on the cpu and send over as uniform)
    f_normal = mat3(transpose(inverse(model))) * v_normal;
    f_tex = v_tex;
}