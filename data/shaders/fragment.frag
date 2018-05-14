#version 330 core

#define NUMBER_POINT_LIGHTS 10

struct
direction_light
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct
point_light
{
    vec3 position;
    vec3 ambient_colour;
    vec3 diffuse_colour;

    float constant;
    float linear;
    float quadratic;
};

out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUv;

uniform vec3 colour;
uniform sampler2D active_texture;

uniform direction_light directional_light;
uniform int active_point_lights = 0;
uniform point_light point_lights[NUMBER_POINT_LIGHTS];

vec3 calculate_dir_light_contribution(direction_light light, vec3 frag_pos, vec3 frag_norm);
vec3 calculate_point_light_contribution(point_light light, vec3 frag_pos, vec3 frag_norm);

void
main()
{
    vec3 objectColor = colour;

    vec3 light_sum = vec3(0.0, 0.0, 0.0);

    light_sum += objectColor * calculate_dir_light_contribution(directional_light, fragPos, fragNormal);

    for (int l = 0; l < active_point_lights; l++)
    {
        light_sum += objectColor * calculate_point_light_contribution(point_lights[l], fragPos, fragNormal);
    }

    fragColor = vec4(light_sum, 1.0) * texture(active_texture, fragUv);
}

vec3
calculate_dir_light_contribution(direction_light light, vec3 frag_pos, vec3 frag_norm)
{
    vec3 light_norm = normalize(-light.direction);
    vec3 norm = normalize(frag_norm);
    float diffuse_contr = max(dot(light_norm, norm), 0);

    vec3 diffuse = diffuse_contr * light.diffuse;
    
    vec3 result = diffuse + light.ambient;
    return result;
}

vec3
calculate_point_light_contribution(point_light light, vec3 frag_pos, vec3 frag_norm)
{
    float distance = length(light.position - frag_pos);
    float attenuation = (1.0 / (light.constant + (light.linear * distance)
                            + (light.quadratic * distance * distance)));

    vec3 ambient = attenuation * light.ambient_colour;

    vec3 norm = normalize(frag_norm);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diffuse_contribution = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diffuse_contribution * light.diffuse_colour;
    diffuse *= attenuation;

    vec3 result = ambient + diffuse;

    return result;
}

