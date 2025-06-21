#shader vertex
#version 330 core

layout(location = 0) in vec3 dummy; // Not used
void main()
{
    // Only used to trigger geometry shader
}

#shader geometry
#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 24) out;

uniform mat4 proj;
uniform mat4 view;
uniform vec3 corners[8]; // frustum corners in world space

void emitLine(int i, int j) {
    gl_Position = proj * view * vec4(corners[i], 1.0);
    EmitVertex();
    gl_Position = proj * view * vec4(corners[j], 1.0);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    // Bottom face
    emitLine(0, 1); emitLine(1, 2);
    emitLine(2, 3); emitLine(3, 0);

    // Top face
    emitLine(4, 5); emitLine(5, 6);
    emitLine(6, 7); emitLine(7, 4);

    // Vertical edges
    emitLine(0, 4); emitLine(1, 5);
    emitLine(2, 6); emitLine(3, 7);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0, 1, 0, 1); // Green frustum lines
}


