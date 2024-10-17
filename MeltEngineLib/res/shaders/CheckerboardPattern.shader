#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec2 fragPos;

void main()
{
    fragPos     = position.xy;
    TexCoord    = texCoord;
    gl_Position = vec4(position, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 fragPos; // Fragment position from vertex shader

vec3 color1 = vec3(0.8, 0.8, 0.8); // Light grey
vec3 color2 = vec3(0.5, 0.5, 0.5); // Dark grey

void main()
{
    float scale = 10.0;
    float pattern = mod(floor(fragPos.x * scale) + floor(fragPos.y * scale), 2.0);
    vec3 color = mix(color1, color2, pattern);
    FragColor = vec4(color, 1.0);
}
