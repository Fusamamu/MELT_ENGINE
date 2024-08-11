#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    //gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
