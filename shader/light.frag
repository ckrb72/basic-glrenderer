#version 410 core

in vec3 frag_pos;
in vec3 f_normal;
in vec2 f_tex;

out vec4 final_color;

uniform vec3 light_color;
uniform vec3 cam_pos;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    //Ambient
    vec3 ambient = material.ambient * light.ambient;

    //Diffuse
    vec3 norm = normalize(f_normal);
    vec3 light_dir = (light.position - frag_pos);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    //Specular
    
    //Need to do this with cam_pos because we are doing things in world space not view space
    //If we were doing it in view space then we would just do (normalize(-frag_pos)) because cam_pos would be (0.0, 0.0, 0.0)
    vec3 cam_dir = normalize(cam_pos - frag_pos);
    vec3 light_reflection = reflect(-light_dir, norm);

    float spec = pow(max(dot(cam_dir, light_reflection), 0.0), material.shininess);
    vec3 specular = (material.specular * spec) * light.specular;

    vec3 result = (ambient + diffuse + specular);
    final_color = vec4(result, 1.0);
}