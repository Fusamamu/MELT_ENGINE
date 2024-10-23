#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fragColor;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
     gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
     fragColor = color;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 fragColor;

void main()
{
    FragColor = vec4(fragColor, 1.0);
}
