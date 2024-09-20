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

const float _Thickness = 0.1;
const float _Scale = 0.08;

float remap(float x, float oldMin, float oldMax, float newMin, float newMax)
{
    return ((x - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
}

float applyScale(float base, float scale)
{
    return floor(fract((base - 0.5 * _Thickness) * scale) + _Thickness * scale);
}

void main()
{
    vec4 _white = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 _black = vec4(0.0, 0.0, 0.0, 0.0);

    float _screenWidth  = ScreenSize.x;
    float _screenHeight = ScreenSize.y;

    const float _cellSize = 50;

    float _x = remap(FragPos.x, -1.0, 1.0, -_screenWidth /2, _screenWidth /2) - Origin.x;
    float _y = remap(FragPos.y, -1.0, 1.0, -_screenHeight/2, _screenHeight/2) + Origin.y;

//     float _logValue = log(_Scale)/log(10.0);
//
//     float xx = ceil(_logValue);
//
//     float xxx = pow(10, xx);
//
//     float xxxx =  _Scale/xxx;

    float logMappedScale = _Scale / pow(10, ceil(log(_Scale)/log(10.0)));
    float localScale = 1 / logMappedScale;

    _x = applyScale(_x, 10.0 * localScale);

    _y = applyScale(_y, 10.0 * localScale);

                   if (_x == 1 || _y == 1) {
                      color = _white;
                   } else {
                      color = _black;
                   }


//     float _rr = float(FragPos.x * 100);
//     color = vec4(vec3(localScale), 1.0);
}
