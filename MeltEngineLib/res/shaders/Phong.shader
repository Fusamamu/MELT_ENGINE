#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;    // Vertex normal

out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 light_space_mat;

out vec3 FragPos;          // Fragment position in world space
out vec3 Normal;           // Normal in world space
out vec3 LightDir;         // Direction from fragment to light
out vec3 ViewDir;          // Direction from fragment to view/camera

uniform vec3 light_world_pos;       // Light position in world space
uniform vec3 light_world_target;
uniform vec3 camera_world_pos;      // Camera position in world space

out vec4 frag_pos_light_space;

void main()
{
    FragPos     = vec3(model * vec4(position, 1.0));             // Compute the fragment position in world space
    Normal      = mat3(transpose(inverse(model))) * normal;      // Transform the normal vector to world space
    TexCoord     = texCoord;
    //LightDir    = light_world_pos - FragPos;                   // Calculate light direction (from fragment to light)
    LightDir    = light_world_pos - light_world_target;
    ViewDir     = camera_world_pos - FragPos;                    // Calculate view direction (from fragment to camera/view)

    frag_pos_light_space = light_space_mat * vec4(FragPos, 1.0); // For shadow mapping

    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 FragPos;       // Fragment position in world space
in vec3 Normal;        // Normal in world space
in vec3 LightDir;      // Direction from fragment to light
in vec3 ViewDir;       // Direction from fragment to view/camera
in vec2 TexCoord;
in vec4 frag_pos_light_space;

uniform vec3 lightColor;       // Light color
uniform vec3 objectColor;      // Object color
uniform float shininess;       // Shininess exponent

uniform sampler2D shadow_map; // shadow texture

// Shadow calculation function
float ShadowCalculation(vec4 _frag_pos_light_space)
{
    // Transform to [0,1] range
    vec3 projCoords = _frag_pos_light_space.xyz / _frag_pos_light_space.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Depth from shadow map
    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // Bias to prevent shadow acne
    float bias = max(0.005 * (1.0 - dot(Normal, normalize(LightDir))), 0.001);

    // Percentage-closer filtering (PCF)
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadow_map, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    shadow /= 9.0;

    // Outside shadow map projection
    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    // Normalize the normal, light direction, and view direction
    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(LightDir);
    vec3 viewDir  = normalize(ViewDir);

    // Ambient lighting (constant low-level light)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting (Lambert's cosine law)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (Phong reflection model)
    vec3 reflectDir = reflect(-lightDir, norm); // Reflection direction
    float spec             = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    float specularStrength = 0.5; // Specular reflection strength
    vec3 specular = specularStrength * spec * lightColor;

    float _shadow = ShadowCalculation(frag_pos_light_space);
    vec3 result = (ambient + (1.0 - _shadow) * (diffuse + specular)) * objectColor;
    //vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);
}
