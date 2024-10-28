#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 NearPoint;
out vec3 FarPoint;

vec3 UnProjectPoint(vec3 _point, mat4 _view, mat4 _proj)
{
    mat4 viewInv = inverse(_view);
    mat4 projInv = inverse(_proj);
    vec4 _unProjectedPoint =  viewInv * projInv * vec4(_point.x, _point.y, _point.z, 1.0);
    return _unProjectedPoint.xyz / _unProjectedPoint.w;
}

void main()
{
    vec3 _nearNDC = vec3(position.x, position.y,-1.0);
    vec3 _farNDC  = vec3(position.x, position.y, 1.0);
    NearPoint = UnProjectPoint(_nearNDC, view, proj);
    FarPoint  = UnProjectPoint(_farNDC , view, proj);
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 NearPoint;
in vec3 FarPoint;

vec4 Grid(vec3 _fragPos3D, float _scale)
{
    vec2 coord      = _fragPos3D.xz * _scale;
    vec2 derivative = fwidth(coord);
    vec2 _grid      = abs(fract(coord - 0.5) - 0.5) / derivative;

    float _line     = min(_grid.x, _grid.y);
    float _minimumZ = min(derivative.y, 1);
    float _minimumX = min(derivative.x, 1);

    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(_line, 1.0));
    // z axis
    if(_fragPos3D.x > -0.2 * _minimumX && _fragPos3D.x < 0.2 * _minimumX)
        color.z = 1.0;
    // x axis
    if(_fragPos3D.z > -0.2 * _minimumZ && _fragPos3D.z < 0.2 * _minimumZ)
        color.x = 1.0;

    return color;
}

void main()
{
    float _t = -NearPoint.y / (FarPoint.y - NearPoint.y);
    vec3 _fragPos = NearPoint + _t * (FarPoint - NearPoint);
    vec4 _color = Grid(_fragPos, 1) * float( _t > 0);
    if(_color.a < 0.1)
        discard;
    FragColor = _color;
}
