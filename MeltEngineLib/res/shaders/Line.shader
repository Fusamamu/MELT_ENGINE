#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader geometry
#version 330 core
layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 p0 = gl_in[0].gl_Position; // Start point of the line
    vec4 p1 = gl_in[1].gl_Position; // End point of the line

    float uThickness = 0.2f;

    vec2 dir = normalize(p1.xy - p0.xy);
    vec2 perp = vec2(-dir.y, dir.x) * uThickness * 0.5;

    vec4 offset = vec4(perp, 0.0, 0.0);

    gl_Position = proj * view * model * (p0 + offset); // First vertex of the quad
    EmitVertex();

    gl_Position = proj * view * model * (p0 - offset); // Second vertex of the quad
    EmitVertex();

    gl_Position = proj * view * model * (p1 + offset); // Third vertex of the quad
    EmitVertex();

    gl_Position = proj * view * model * (p1 - offset); // Fourth vertex of the quad
    EmitVertex();

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
