#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;

out vec2 TexCoords;

void main()
{
    TexCoords   = texCoord;
    gl_Position = vec4(position.xy, 0.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 TexCoords;

uniform sampler2D depthMap;

out vec4 FragColor;

float LinearizeDepth(float depth)
{
    float near = 1.0;
    float far = 100.0;
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{

    float _depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(_depthValue), 1.0); // grayscale visualization


    //float depth = texture(depthMap, TexCoords).r;
    //float linear = LinearizeDepth(depth) / 100.0;
    //FragColor = vec4(vec3(linear), 1.0);

}


