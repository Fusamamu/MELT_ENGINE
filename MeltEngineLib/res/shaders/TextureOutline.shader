#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
    TexCoord = texCoord;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec2 TexCoord;

uniform vec3 Color;
uniform sampler2D Texture;

void main()
{
    vec3 outlineColor = vec3(1.0, 0.0, 0.0);

    vec2 texelSize;

    texelSize.x = 0.005;
    texelSize.y = 0.005;

    vec4 centerColor = texture(Texture, TexCoord);

    vec4 up    = texture(Texture, TexCoord + vec2(0.0, texelSize.y));
    vec4 down  = texture(Texture, TexCoord - vec2(0.0, texelSize.y));
    vec4 left  = texture(Texture, TexCoord - vec2(texelSize.x, 0.0));
    vec4 right = texture(Texture, TexCoord + vec2(texelSize.x, 0.0));

    if (centerColor.a < 0.1)
    {
        if (up.a > 0.1 || down.a > 0.1 || left.a > 0.1 || right.a > 0.1)
        {
            color = vec4(outlineColor, 1.0);
            return;
        }
    }
    color = centerColor;
}
