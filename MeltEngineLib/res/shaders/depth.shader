#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;    // Vertex normal

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core

void main()
{
    // empty – we only care about depth
    gl_FragDepth = gl_FragCoord.z;
}

