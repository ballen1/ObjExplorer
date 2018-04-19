#version 330 core

#define NUMBER_POINT_LIGHTS 10

struct
point_light
{
    vec3 position;
    vec3 colour;

    float ambient_strength;
    float diffuse_strength;
};

out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 colour;

uniform int active_point_lights = 0;
uniform point_light point_lights[NUMBER_POINT_LIGHTS];

vec3 calculate_point_light_contribution(point_light light, vec3 frag_pos, vec3 frag_norm);

void
main()
{
    vec3 objectColor = colour;

    vec3 light_sum = vec3(0.0, 0.0, 0.0);

    for (int l = 0; l < active_point_lights; l++)
    {
        light_sum += objectColor * calculate_point_light_contribution(point_lights[l], fragPos, fragNormal);
    }

    fragColor = vec4(light_sum, 1.0);
}

vec3
calculate_point_light_contribution(point_light light, vec3 frag_pos, vec3 frag_norm)
{
    vec3 ambient = light.ambient_strength * light.colour;

    vec3 norm = normalize(frag_norm);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diffuse_contribution = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diffuse_contribution * light.colour;

    vec3 result = ambient + diffuse;

    return result;
}

