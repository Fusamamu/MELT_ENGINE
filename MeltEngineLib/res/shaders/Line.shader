#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec3 Color;

void main()
{
    FragColor = vec4(Color.r, Color.g, Color.b, 1.0);
}
