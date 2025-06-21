#shader vertex
#version 330 core

layout(location = 0) in vec3 aabbMin;
layout(location = 1) in vec3 aabbMax;

out VS_OUT {
    vec3 min;
    vec3 max;
} vs_out;

void main() {
    vs_out.min = aabbMin;
    vs_out.max = aabbMax;
}

#shader geometry
#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 24) out;

uniform mat4 viewProj;

in VS_OUT {
    vec3 min;
    vec3 max;
} gs_in[];

void EmitLine(vec3 a, vec3 b) {
    gl_Position = viewProj * vec4(a, 1.0);
    EmitVertex();
    gl_Position = viewProj * vec4(b, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main() {
    vec3 min = gs_in[0].min;
    vec3 max = gs_in[0].max;

    vec3 corners[8] = vec3[](
        vec3(min.x, min.y, min.z), // 0
        vec3(max.x, min.y, min.z), // 1
        vec3(max.x, max.y, min.z), // 2
        vec3(min.x, max.y, min.z), // 3
        vec3(min.x, min.y, max.z), // 4
        vec3(max.x, min.y, max.z), // 5
        vec3(max.x, max.y, max.z), // 6
        vec3(min.x, max.y, max.z)  // 7
    );

    // Bottom face
    EmitLine(corners[0], corners[1]);
    EmitLine(corners[1], corners[2]);
    EmitLine(corners[2], corners[3]);
    EmitLine(corners[3], corners[0]);

    // Top face
    EmitLine(corners[4], corners[5]);
    EmitLine(corners[5], corners[6]);
    EmitLine(corners[6], corners[7]);
    EmitLine(corners[7], corners[4]);

    // Sides
    EmitLine(corners[0], corners[4]);
    EmitLine(corners[1], corners[5]);
    EmitLine(corners[2], corners[6]);
    EmitLine(corners[3], corners[7]);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0); // Yellow AABB
}

