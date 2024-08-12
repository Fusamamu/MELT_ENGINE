#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;

void main()
{
    FragPos = position;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 FragPos;

float remap(float x, float oldMin, float oldMax, float newMin, float newMax)
{
    return ((x - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
}

void main()
{
    vec4 _white = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 _black = vec4(0.0, 0.0, 0.0, 0.0);

//     float _x = mod(FragPos.x, 1.0);
//     float _y = mod(FragPos.y, 0.1);
//
//     float _remapX = remap(FragPos.x, -1.0, 1.0, 0.0, 800.0);
//     float _remapY = remap(FragPos.y, -1.0, 1.0, 0.0, 600.0);
//
//     vec3 _r = vec3(mod(_remapX, 50.0));


 // Scale factor to determine the size of the checkerboard squares
    float scale = 10.0;

    // Determine the position in the checkerboard grid
    float checkerX = mod(floor(FragPos.x * scale), 2.0);
    float checkerY = mod(floor(FragPos.y * scale), 2.0);

    // Calculate whether the fragment is on a black or white square
    float checker = mod(checkerX + checkerY, 2.0);

    // Set the color based on the checkerboard pattern
    color = mix(_white, _black, checker);

    //color = vec4(vec3(_r), 1.0);

    //color = vec4(FragPos.x, FragPos.y, FragPos.z,  1.0);



}
