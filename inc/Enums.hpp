
#ifndef ENUMS_HPP
#define ENUMS_HPP

enum SAL3D
{
    SAL3D_vertex = 0,
    SAL3D_normal = 1,
    SAL3D_texCoord = 2,
    SAL3D_ka = 10,
    SAL3D_kd = 11,
    SAL3D_ks = 12,
    SAL3D_ns = 13,
    SAL3D_NUM = 7
};

enum SUL3D
{
    SUL3D_MM = 0,
    SUL3D_VM = 1,
    SUL3D_PM = 2,
    SUL3D_textured = 10,
    SUL3D_numLights = 20,
    SUL3D_lights = 21,
    SUL3D_NUM = 5
};


enum SAL2D
{
    SAL2D_vertex = 0,
    SAL2D_texCoord = 1,
    SAL2D_NUM = 2
};

enum SUL2D
{
    SUL2D_MM = 0,
    SUL2D_WM = 1,
    SUL2D_textured = 10,
    SUL2D_color = 20,
    SUL2D_NUM = 4
};

#endif