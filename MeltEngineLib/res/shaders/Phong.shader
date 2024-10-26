#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;
layout(location = 4) in vec3 normal;    // Vertex normal

out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightWorldPos;     // Light position in world space
uniform vec3 cameraWorldPos;      // Camera position in world space

out vec3 FragPos;          // Fragment position in world space
out vec3 Normal;           // Normal in world space
out vec3 LightDir;         // Direction from fragment to light
out vec3 ViewDir;          // Direction from fragment to view/camera

void main()
{
    // Compute the fragment position in world space
    FragPos = vec3(model * vec4(position, 1.0));
    // Transform the normal vector to world space
    Normal = mat3(transpose(inverse(model))) * normal;
    // Calculate light direction (from fragment to light)
    LightDir = lightWorldPos - FragPos;
    // Calculate view direction (from fragment to camera/view)
    ViewDir = cameraWorldPos - FragPos;
    // Transform vertex position for the final position output
    //gl_Position = projection * view * vec4(FragPos, 1.0);

    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
    TexCoord = texCoord;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 FragPos;       // Fragment position in world space
in vec3 Normal;        // Normal in world space
in vec3 LightDir;      // Direction from fragment to light
in vec3 ViewDir;       // Direction from fragment to view/camera
in vec2 TexCoord;

uniform vec3 lightColor;       // Light color
uniform vec3 objectColor;      // Object color
uniform float shininess;       // Shininess exponent

// uniform vec3 Color;
// uniform sampler2D Texture;

void main()
{
    // Normalize the normal, light direction, and view direction
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightDir);
    vec3 viewDir = normalize(ViewDir);

    // Ambient lighting (constant low-level light)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting (Lambert's cosine law)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (Phong reflection model)
    vec3 reflectDir = reflect(-lightDir, norm); // Reflection direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    float specularStrength = 0.5; // Specular reflection strength
    vec3 specular = specularStrength * spec * lightColor;

    // Combine all three components
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
