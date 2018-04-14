#version 330 core

#define NUMBER_POINT_LIGHTS 10

struct
point_light
{
    vec3 position;
    vec3 colour;
};

out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 colour;

void
main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(-500, 500, 500);
    vec3 objectColor = colour;
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0);
}

vec3
calculate_point_light_contribution(point_light light)
{
    return vec3(0, 0, 0);
}

