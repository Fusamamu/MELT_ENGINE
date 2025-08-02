#shader vertex
#version 330 core
layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

out vec2 v_uv;
out vec4 v_color;

uniform vec2 u_position;
uniform vec2 u_size;
uniform mat4 u_proj;

void main()
{
    vec2 scaled_pos = a_pos * u_size + u_position;
    gl_Position = u_proj * vec4(scaled_pos, 0.0, 1.0);
    v_uv    = a_uv;
    v_color = a_color;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 v_uv;
in vec4 v_color;

uniform sampler2D u_texture;

void main()
{
    vec4 tex_color = texture(u_texture, v_uv);
    FragColor = tex_color * v_color;

    FragColor = v_color;
}
