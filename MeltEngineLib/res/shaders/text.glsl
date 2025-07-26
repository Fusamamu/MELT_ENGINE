#shader vertex
#version 330 core
layout(location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 proj;

void main()
{
    gl_Position = proj * vec4(vertex.x, vertex.y,  0.0, 1.0);
    TexCoords   = vertex.zw;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D text;
uniform vec3 text_color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    FragColor = vec4(text_color, 1.0) * sampled;
}
