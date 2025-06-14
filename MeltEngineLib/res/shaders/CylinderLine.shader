#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0);
}

#shader geometry
#version 330 core

layout(lines) in;
layout(triangle_strip, max_vertices = 64) out;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

const int slices = 16;
uniform float radius = 0.02;

void main() {
    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 dir = normalize(p1 - p0);

    // Find a vector perpendicular to dir
    vec3 up = abs(dir.y) < 0.999 ? vec3(0, 1, 0) : vec3(1, 0, 0);
    vec3 side = normalize(cross(dir, up));
    vec3 upVec = normalize(cross(side, dir));

    for (int i = 0; i <= slices; ++i) {
        float theta = (2.0 * 3.14159 * i) / slices;
        vec3 offset = radius * (cos(theta) * side + sin(theta) * upVec);

        vec4 v0 = proj * view * vec4(p0 + offset, 1.0);
        vec4 v1 = proj * view * vec4(p1 + offset, 1.0);

        gl_Position = v0;
        EmitVertex();

        gl_Position = v1;
        EmitVertex();
    }

    EndPrimitive();
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec3 Color;

void main()
{
    FragColor = vec4(Color.r, Color.g, Color.b, 1.0);
}
