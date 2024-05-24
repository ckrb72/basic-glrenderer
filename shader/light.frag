#version 410 core

in vec3 frag_pos;
in vec3 f_normal;
in vec2 f_tex;

out vec4 final_color;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 cam_pos;

vec3 object_color = vec3(0.7, 0.7, 0.7);

void main()
{
    //Ambient
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    //Diffuse
    vec3 norm = normalize(f_normal);
    vec3 light_dir = (light_pos - frag_pos);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    //Specular
    float specular_strength = 0.5;

    //Need to do this with cam_pos because we are doing things in world space not view space
    //If we were doing it in view space then we would just do (normalize(-frag_pos)) because cam_pos would be (0.0, 0.0, 0.0)
    vec3 cam_dir = normalize(cam_pos - frag_pos);
    vec3 light_reflection = reflect(-light_dir, norm);

    float spec = pow(max(dot(cam_dir, light_reflection), 0.0), 2);
    vec3 specular = specular_strength * spec * light_color;

    vec3 result = (ambient + diffuse + specular) * object_color;
    final_color = vec4(result, 1.0);
}