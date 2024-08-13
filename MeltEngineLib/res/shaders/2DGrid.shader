#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform vec2 screenSize;
uniform vec2 origin;

out vec3 FragPos;
out vec2 ScreenSize;
out vec2 Origin;

void main()
{
    FragPos     = position;
    ScreenSize  = screenSize;
    Origin      = origin;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec2 ScreenSize;
in vec2 Origin;

float remap(float x, float oldMin, float oldMax, float newMin, float newMax)
{
    return ((x - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
}

void main()
{
    vec4 _white = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 _black = vec4(0.0, 0.0, 0.0, 0.0);

    float _screenWidth  = ScreenSize.x;
    float _screenHeight = ScreenSize.y;

    float _cellSize = 50;


    vec2 _offset = vec2(100, 100);



    float _x = remap(FragPos.x, -1.0, 1.0, -_screenWidth /2, _screenWidth /2) - Origin.x;
    float _y = remap(FragPos.y, -1.0, 1.0, -_screenHeight/2, _screenHeight/2) + Origin.y;

    float _axisX = 1 - step(0.7, mod(_x, 400));
    float _axisY = 1 - step(0.7, mod(_y, 300));

    float _axis = max(_axisX, _axisY);

    vec3 _axisCol = vec3(1.0, 0.0, 0.0) * _axis;


    _x = step(0.4, mod(_x, 50));
    _y = step(0.4, mod(_y, 50));
    float _r = min(_x, _y);

    color = vec4(vec3(_r) + _axisCol, 1.0);
}
